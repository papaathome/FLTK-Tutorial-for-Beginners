BEGIN { OF = ""; path="./" }
/^\/\/ example[0-9]+\.cpp: """$/ && (OF == "") {
        gsub(/^\/\/[ \t]+/, "", $0)
        gsub(/:.*$/, "", $0)
        OF = $0
        $0 = "// " OF
        OF = path OF
        print "" > OF
    }
/^\/\/ """$/ && (OF != "") { print "" >> OF; OF = ""; }
(OF != "") { print >> OF }
