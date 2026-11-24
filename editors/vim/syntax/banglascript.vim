" Vim syntax file for BanglaScript (.bs)
if exists("b:current_syntax")
  finish
endif

syntax keyword bsType sonkha dosomik bakya sotti shunno সংখ্যা দশমিক বাক্য সত্যি শূন্য
syntax keyword bsKeyword jodi nahole jotokhon bondho chaliyejao kaj ferot যদি নাহলে যতক্ষণ বন্ধ চালিয়েযাও কাজ ফেরত
syntax keyword bsBuiltin dekhao nao দেখাও নাও
syntax keyword bsBoolean true false
syntax match bsNumber "\v<\d+(\.\d+)?>"
syntax match bsBengaliNumber "\v<[০-৯]+(\.[০-৯]+)?>"
syntax match bsComment "//.*$"
syntax region bsCommentBlock start="/\*" end="\*/"
syntax region bsString start='"' end='"' skip='\\"'

highlight default link bsType Type
highlight default link bsKeyword Keyword
highlight default link bsBuiltin Function
highlight default link bsBoolean Boolean
highlight default link bsNumber Number
highlight default link bsBengaliNumber Number
highlight default link bsComment Comment
highlight default link bsCommentBlock Comment
highlight default link bsString String

let b:current_syntax = "banglascript"
