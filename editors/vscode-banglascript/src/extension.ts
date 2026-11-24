import * as vscode from 'vscode';
import * as cp from 'child_process';
import * as path from 'path';

let diagnosticCollection: vscode.DiagnosticCollection;

export function activate(context: vscode.ExtensionContext) {
    diagnosticCollection = vscode.languages.createDiagnosticCollection('banglascript');
    context.subscriptions.push(diagnosticCollection);

    // Register Commands
    context.subscriptions.push(
        vscode.commands.registerCommand('banglascript.run', () => runCurrentFile(context)),
        vscode.commands.registerCommand('banglascript.check', () => checkCurrentFile(context)),
        vscode.commands.registerCommand('banglascript.compile', () => compileCurrentFile(context)),
        vscode.commands.registerCommand('banglascript.ast', () => showAST(context)),
        vscode.commands.registerCommand('banglascript.tac', () => showTAC(context))
    );

    // Validate on file save
    context.subscriptions.push(
        vscode.workspace.onDidSaveTextDocument(document => {
            if (document.languageId === 'banglascript') {
                runDiagnostics(document);
            }
        })
    );

    // Initial check for active editor
    if (vscode.window.activeTextEditor?.document.languageId === 'banglascript') {
        runDiagnostics(vscode.window.activeTextEditor.document);
    }
}

function getExecutablePath(): string {
    const config = vscode.workspace.getConfiguration('banglascript');
    return config.get<string>('executablePath', 'banglascript');
}

function runCurrentFile(context: vscode.ExtensionContext) {
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
    terminal.sendText(`${exe} run "${filePath}"`);
}

function checkCurrentFile(context: vscode.ExtensionContext) {
    const editor = vscode.window.activeTextEditor;
    if (!editor) return;
    runDiagnostics(editor.document, true);
}

function compileCurrentFile(context: vscode.ExtensionContext) {
    const editor = vscode.window.activeTextEditor;
    if (!editor) return;

    const exe = getExecutablePath();
    const filePath = editor.document.fileName;

    const terminal = vscode.window.terminals.find(t => t.name === 'BanglaScript') ||
                     vscode.window.createTerminal('BanglaScript');
    terminal.show();
    terminal.sendText(`${exe} compile "${filePath}"`);
}

function showAST(context: vscode.ExtensionContext) {
    const editor = vscode.window.activeTextEditor;
    if (!editor) return;

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

function showTAC(context: vscode.ExtensionContext) {
    const editor = vscode.window.activeTextEditor;
    if (!editor) return;

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

function runDiagnostics(document: vscode.TextDocument, showSuccessNotification = false) {
    const exe = getExecutablePath();
    const filePath = document.fileName;

    cp.exec(`"${exe}" check "${filePath}"`, (err, stdout, stderr) => {
        const diagnostics: vscode.Diagnostic[] = [];

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
        } else {
            diagnosticCollection.delete(document.uri);
            if (showSuccessNotification) {
                vscode.window.showInformationMessage('BanglaScript: Validation successful (0 errors).');
            }
        }
    });
}

function escapeHtml(text: string): string {
    return text.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
}

export function deactivate() {
    if (diagnosticCollection) {
        diagnosticCollection.clear();
    }
}
