# inode-graph

This is my i-node graph programming assignment.

To compile, you run the command, "gcc -g inodeGraph.c -o Inode"
This will create an Inode file just like a.out file.
To run, you will type "./Inode Directory name/path".
Running ./Inode will generate a .gv (Graphviz) file, named as "Filenode.gv".
To convert .gv file into pdf file, you will run the command, "dot -Tpdf:cairo Filenode.gv -o Filenode.pdf".
The above line will create a pdf file which you can open and see the pretty i-node graph.

For my program, I have created a test directory named INtest. I use that as directory name when I run ./Inode command.
SO the pdf file containing i-node graph is about that INtest directory.
