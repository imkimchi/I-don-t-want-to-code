#!/bin/sh

DEFAULT_URI="https://github.com/imkimchi/dont_code_anymore/blob/master/"
FILE_NAMES=("gcc" "python" "node" "apt-get" "rm" "brew")

function download(){
   curl -LO 2>/dev/null "${DEFAULT_URI}$1"
   chmod +x $1
}

function movetoPATH(){
  if test -e $1
  then
    mv -f $1 /usr/local/bin/
  else
    echo "failed to load file"
    exit
  fi
}

for value in "${FILE_NAMES[@]}"; do
   download $value
   movetoPATH $value
done
