#!/bin/awk -f

BEGIN { FS = "\t"; } 

/^[^#].*\t.+$/ { 
    printf "%-30s\t\x1b[36m%s\x1b[m\n", $1, $2;
}
