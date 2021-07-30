# Linux Tree Command
This project is to implement the linux tree command in C language. The tree is a tiny cross-platform command-line program . The tree command displays the contents of a particular directory in a tree like format.
Color codes are also used to display files and folders.
This project can be run on ubuntu by giving the following command
./tree -flag
The flags that I have implemented are :
•-a : All files are printed. By default tree does not print hidden files(those begin with dot ("."). In no event does the tree print the file system constructs '.' (current directory) and '..' (previous directory).
•-d : List directories only.
•-f : Prints the full path prefix for each sub-directory and file.
•-Q : Will print the file names in double quotes.
•-L level : Maximum display depth of the directory tree.
•-i : Makes tree not print the indentation lines.
 
•-p : To print the protections for each file.
•-s : To print the size of each file.
•-D : Prints the date of last modification time for file..
•-u : Prints username, or UID.
•-g : Prints group name, or GID.
•-S : Turns on ASCII line graphics.
•-n : Will print the directory tree without colors.
•-X : Prints XML representation of the tree.
•-J : Prints JSON representation of the tree.
•-P pattern : Will list only those files that will match the pattern.
•-I pattern : Does not list files that match the pattern.
•-–help : Outputs a verbose usage listing.
•--version : Prints version.
