function clear() {
    document.getElementById( "num1" ).value = ''
    document.getElementById( "num2" ).value = ''
}

function compute( button ) {
    let num1_element = document.getElementById( "num1" )
    let num2_element = document.getElementById( "num2" )
    let num1 = parseInt( num1_element.value )
    let num2 = parseInt( num2_element.value )
    if( isNaN( num1 ) || isNaN( num2 ) ) {
        alert( "Invalid numbers given!" )
        num1_element.value = "" 
        num2_element.value = ""
        return
    }
    let operation = button.value
    let result = 0 ;
    switch( operation ) {
        case "+":
            result = num1 + num2 
            break
        case "-":
            result = num1 - num2 
            break
        case "*":
            result = num1 * num2 
            break
        case "/":
            result = num1 / num2 
            break
    }
    num1_element.value = result.toString()
    num2_element.value = ""
}