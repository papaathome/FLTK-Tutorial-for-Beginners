#! /usr/bin/bash
#
# ParseTurotial - extract examples from the tutorial v2.

# $1 - path to pdf file.
# $2 - path to output directory, default to "./"


if [ -f "$1" ]; then
    if [ -d "$2" ]; then
        if [[ "$2" != */ ]]; then
            path="$2/"
        else
            path="$2"
        fi
    else
        path="./"
    fi

    doc2txt="pdftotext -q -nopgbrk -raw $1 -"
    filter="awk -f extract.awk"
    formatter="clang-format"
    split="awk -f split.awk path=$path"
    $doc2txt | $filter | $formatter | $split
else    
    echo "usage: ./ParseTutorial.sh path/to/pdf [ path/to/output/dir/ ]"
    echo "  where pdf is the version 2 (or better) tutorial file."
    echo "  all output to file names from the example delimiters."
    echo "  default output path for the example files is ./"
fi

