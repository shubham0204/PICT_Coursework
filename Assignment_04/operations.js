function clear() {
    document.getElementById( "num1" ).value = ''
    document.getElementById( "num2" ).value = ''
}

function percent() {
    let num1_element = document.getElementById( "num1" )
    let num2_element = document.getElementById( "num2" )
    let num1 = parseInt( num1_element.value )
    let num2 = parseInt( num2_element.value )
    if( isNaN( num1 ) || isNaN( num2 ) || num1 < 0 || num2 < 0 ) {
        alert( "Invalid numbers given!" )
        num1_element.value = "" 
        num2_element.value = ""
        return
    }
    let result = ( num1 / num2 ) * 100
    num1_element.value = result.toString()
    num2_element.value = ""
}

function sqrt() {
    let num1_element = document.getElementById( "num1" )
    let num1 = parseInt( num1_element.value )
    if( num1 < 0 ) {
        alert( "sqrt cannot be performed on negative numbers" )
        return
    }
    let res = Math.sqrt( num1 )
    num1_element.value = res.toString()
    num2_element.value = ""
}

function sqr() {
    let num1_element = document.getElementById( "num1" )
    let num1 = parseInt( num1_element.value )
    let res = num1 * num1
    num1_element.value = res.toString()
    num2_element.value = ""
}

function cbrt() {
    let num1_element = document.getElementById( "num1" )
    let num1 = parseInt( num1_element.value )
    let res = Math.cbrt( num1 )
    num1_element.value = res.toString()
    num2_element.value = ""
}

function cube() {
    let num1_element = document.getElementById( "num1" )
    let num1 = parseInt( num1_element.value )
    let res = num1 * num1 * num1
    num1_element.value = res.toString()
    num2_element.value = ""
}

function m_to_ft() {
    let num1_element = document.getElementById( "num1" )
    let num1 = parseInt( num1_element.value )
    if( num1 < 0 ) {
        alert( "metres cannot be negative" )
        return
    }
    let res = 3.28084 * num1
    num1_element.value = res.toString()
    num2_element.value = ""
}

function c_to_f() {
    let num1_element = document.getElementById( "num1" )
    let num1 = parseInt( num1_element.value )
    let res = (num1 * (9/5)) + 32
    num1_element.value = res.toString()
    num2_element.value = ""
}

function gram_to_pound() {
    let num1_element = document.getElementById( "num1" )
    let num1 = parseInt( num1_element.value )
    if( num1 < 0 ) {
        alert( "grams cannot be negative" )
        return
    }
    let res = 0.00220462 * num1
    num1_element.value = res.toString()
    num2_element.value = ""
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