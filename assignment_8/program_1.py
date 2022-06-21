
# Problem Statement:
# Write a program in Python to count total characters in file,
# total words in file, total lines in file and frequency of given word in file.

# Opening the file in read-only mode and reading its content
filename = input( 'Enter a filename ( .txt ) : ')
file = open( filename , 'r' )
file_content = file.read().strip()
file.close()

num_chars = len( file_content )
print( 'Number of characters in given file :' , num_chars )

num_words = len( file_content.split() )
print( 'Number of words in given file :' , num_words )

num_lines = len( file_content.splitlines() )
print( 'Number of lines in given file :' , num_lines )

input_word = input( 'Enter a word from the text : ' )
freq = file_content.count( input_word )
if freq == 0:
    print( '{} does not exist in the text.'.format( input_word ) )
else:
    print( 'Frequency of {} in the text is'.format( input_word ) , freq )