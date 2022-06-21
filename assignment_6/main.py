
# Write a Program in Python to input binary number from user and convert it into decimal number.

radix = int( input( 'Enter the base of the number : ') )
a = input( 'Enter a number : ')
a = int( a , base=radix )
print( 'The number in decimal is' , a )


