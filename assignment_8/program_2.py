
# Problem Statement
# Write a Program in Python to copy contents of one file to other. While copying
# a) all full stops are to be replaced with commas
# b) lower case are to be replaced with upper case
# c) upper case are to be replaced with lower case.

# Opening the file in read-only mode and reading its content
filename = input( 'Enter input filename ( .txt ) : ')
file = open( filename , 'r' )
file_content = file.read().strip()
file.close()

# Replace full stops with comma
file_content = file_content.replace( '.' , ',' )
# Swap text cases
file_content = file_content.swapcase()

out_filename = input( 'Enter output filename ( .txt ) : ')
file = open( out_filename , 'w' )
file.write( file_content )
file.close()
