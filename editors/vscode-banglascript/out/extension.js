"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.activate = activate;
exports.deactivate = deactivate;
const vscode = require("vscode");
const cp = require("child_process");
const path = require("path");
const fs = require("fs");
let diagnosticCollection;
let runStatusBarItem;
function activate(context) {
    diagnosticCollection = vscode.languages.createDiagnosticCollection('banglascript');
    context.subscriptions.push(diagnosticCollection);
    // Status bar item to run BanglaScript files
    runStatusBarItem = vscode.window.createStatusBarItem(vscode.StatusBarAlignment.Left, 100);
    runStatusBarItem.command = 'banglascript.run';
    runStatusBarItem.text = '$(play) Run BanglaScript';
    runStatusBarItem.tooltip = 'Click to compile and execute with BanglaScript VM';
    context.subscriptions.push(runStatusBarItem);
    // Register Commands
    context.subscriptions.push(vscode.commands.registerCommand('banglascript.run', () => runCurrentFile(context)), vscode.commands.registerCommand('banglascript.check', () => checkCurrentFile(context)), vscode.commands.registerCommand('banglascript.compile', () => compileCurrentFile(context)), vscode.commands.registerCommand('banglascript.ast', () => showAST(context)), vscode.commands.registerCommand('banglascript.tac', () => showTAC(context)));
    // Update status bar item on editor switch
    context.subscriptions.push(vscode.window.onDidChangeActiveTextEditor(editor => {
        updateStatusBarItem(editor);
    }));
    // Validate on file save
    context.subscriptions.push(vscode.workspace.onDidSaveTextDocument(document => {
        if (document.languageId === 'banglascript') {
            runDiagnostics(document);
        }
    }));
    // Initial check for active editor
    if (vscode.window.activeTextEditor) {
        updateStatusBarItem(vscode.window.activeTextEditor);
        if (vscode.window.activeTextEditor.document.languageId === 'banglascript') {
            runDiagnostics(vscode.window.activeTextEditor.document);
        }
    }
}
function updateStatusBarItem(editor) {
    if (editor && (editor.document.languageId === 'banglascript' || editor.document.fileName.endsWith('.bs'))) {
        runStatusBarItem.show();
    }
    else {
        runStatusBarItem.hide();
    }
}
function getExecutablePath() {
    const config = vscode.workspace.getConfiguration('banglascript');
    const customPath = config.get('executablePath', 'banglascript');
    if (customPath && customPath !== 'banglascript' && fs.existsSync(customPath)) {
        return customPath;
    }
    // Auto-detect binary in current workspace build/bin/
    const workspaceFolders = vscode.workspace.workspaceFolders;
    if (workspaceFolders) {
        for (const folder of workspaceFolders) {
            const isWin = process.platform === 'win32';
            const exeName = isWin ? 'banglascript.exe' : 'banglascript';
            const candidate = path.join(folder.uri.fsPath, 'build', 'bin', exeName);
            if (fs.existsSync(candidate)) {
                return candidate;
            }
        }
    }
    return customPath || 'banglascript';
}
function runCurrentFile(context) {
    const editor = vscode.window.activeTextEditor;
    if (!editor) {
        vscode.window.showErrorMessage('No active BanglaScript file to run.');
        return;
    }
    const document = editor.document;
    if (document.isDirty) {
        document.save();
    }
    const filePath = document.fileName;
    const exe = getExecutablePath();
    const terminal = vscode.window.terminals.find(t => t.name === 'BanglaScript') ||
        vscode.window.createTerminal('BanglaScript');
    terminal.show();
    // Use PowerShell call operator & on Windows, or direct execution on Unix
    const isWin = process.platform === 'win32';
    const command = isWin ? `& "${exe}" run "${filePath}"` : `"${exe}" run "${filePath}"`;
    terminal.sendText(command);
}
function checkCurrentFile(context) {
    const editor = vscode.window.activeTextEditor;
    if (!editor)
        return;
    runDiagnostics(editor.document, true);
}
function compileCurrentFile(context) {
    const editor = vscode.window.activeTextEditor;
    if (!editor)
        return;
    const exe = getExecutablePath();
    const filePath = editor.document.fileName;
    const terminal = vscode.window.terminals.find(t => t.name === 'BanglaScript') ||
        vscode.window.createTerminal('BanglaScript');
    terminal.show();
    const isWin = process.platform === 'win32';
    const command = isWin ? `& "${exe}" compile "${filePath}"` : `"${exe}" compile "${filePath}"`;
    terminal.sendText(command);
}
function showAST(context) {
    const editor = vscode.window.activeTextEditor;
    if (!editor)
        return;
    const exe = getExecutablePath();
    const filePath = editor.document.fileName;
    cp.exec(`"${exe}" ast "${filePath}"`, (err, stdout, stderr) => {
        if (err) {
            vscode.window.showErrorMessage(`AST Generation Error: ${stderr || err.message}`);
            return;
        }
        const panel = vscode.window.createWebviewPanel('banglascriptAST', 'BanglaScript AST', vscode.ViewColumn.Beside, {});
        panel.webview.html = `<html><body><pre style="font-family: monospace; padding: 16px;">${escapeHtml(stdout)}</pre></body></html>`;
    });
}
function showTAC(context) {
    const editor = vscode.window.activeTextEditor;
    if (!editor)
        return;
    const exe = getExecutablePath();
    const filePath = editor.document.fileName;
    cp.exec(`"${exe}" tac "${filePath}" --opt`, (err, stdout, stderr) => {
        if (err) {
            vscode.window.showErrorMessage(`TAC Generation Error: ${stderr || err.message}`);
            return;
        }
        const panel = vscode.window.createWebviewPanel('banglascriptTAC', 'BanglaScript TAC', vscode.ViewColumn.Beside, {});
        panel.webview.html = `<html><body><pre style="font-family: monospace; padding: 16px;">${escapeHtml(stdout)}</pre></body></html>`;
    });
}
function runDiagnostics(document, showSuccessNotification = false) {
    const exe = getExecutablePath();
    const filePath = document.fileName;
    cp.exec(`"${exe}" check "${filePath}"`, (err, stdout, stderr) => {
        const diagnostics = [];
        if (err) {
            const output = stderr || stdout;
            // Parse error lines: <file>:<line>:<col>: error: <msg>
            const regex = /([^:\n]+):(\d+):(\d+):\s*(error|warning):\s*(.*)/g;
            let match;
            while ((match = regex.exec(output)) !== null) {
                const line = Math.max(0, parseInt(match[2], 10) - 1);
                const col = Math.max(0, parseInt(match[3], 10) - 1);
                const severity = match[4] === 'warning' ? vscode.DiagnosticSeverity.Warning : vscode.DiagnosticSeverity.Error;
                const message = match[5];
                const range = new vscode.Range(line, col, line, col + 10);
                diagnostics.push(new vscode.Diagnostic(range, message, severity));
            }
            diagnosticCollection.set(document.uri, diagnostics);
        }
        else {
            diagnosticCollection.delete(document.uri);
            if (showSuccessNotification) {
                vscode.window.showInformationMessage('BanglaScript: Validation successful (0 errors).');
            }
        }
    });
}
function escapeHtml(text) {
    return text.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
}
function deactivate() {
    if (diagnosticCollection) {
        diagnosticCollection.clear();
    }
}
//# sourceMappingURL=extension.js.map