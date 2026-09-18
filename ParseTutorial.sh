#! /usr/bin/bash
#
# ParseTurotial - extract examples from the tutorial v2.

if [ -f "$1" ]; then
    doc2txt="pdftotext -q -nopgbrk -raw $1 -"
    filter="awk -f extract.awk"
    formatter="clang-format"
    split="awk -f split.awk"
    $doc2txt | $filter | $formatter | $split
else    
    echo "usage: ./ParseTutorial.sh pdf"
    echo "  where pdf is the version 2 (or better) tutorial file."
    echo "  all output to file names from the example delimiters."
fi

