#!/bin/bash

(grep "OK DOWNLOAD" cdlinux.ftp.log | cut -d '"' -f 2,4 | grep ".iso$" | sed 's#"# #g' && 
grep -E " 200 | 206 " cdlinux.www.log | grep "GET" | cut -d " " -f 1,7  | cut -d ":" -f 2 | grep ".iso$" | sed 's#\%2F#\/#g') | 
sort -u | sed "s#.*/##" | sort | uniq -c | sort -r > result.txt;
