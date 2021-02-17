# Competitve Programming

## About
This is a C++ algorithm and data structure library written from scratch.   
Verified mainly on [Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/home) and competitve programming sites such as [AtCoder](https://atcoder.jp).  
This library also provides an easy way to add the algorithms and data structures to your Visual Studio Code snippets. 

## Usage
Add setting.json file in the same directoly as s```nipet.py```, then edit the file like below.
```
{
  "path": "./src",
  "json_path": "../.vscode/temp.code-snippets",
  "indent": 2
}
```
```"path"``` stands for the path to the directoly which contains source codes of algolithms. All files under this directory will be recursively added to snippents of Visual Studio Code when the command is excuted.  
```"json_path"``` stands for the path to the snippets file of Visual Studio Code.  
```"indent"``` stands for the length of indent.

To add all algorithms and data structures in your snippets, just excute this command.
```
$ python snippet.py
```