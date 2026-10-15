BEGIN { in_code = 0; print "// {{{" }

/^example[0-9]+\.cpp: """$/ && (in_code == 0) { in_code = 1; $0 = "// " $0  }
/^"""$/ && (in_code != 0) { in_code = 0; print "// " $0 "\n" }

(in_code != 0) && /^int main\(/ { $0 = "int fl_main(int argc, char **argv) {" }
(in_code != 0) { print }

END { print "// }}}" }
