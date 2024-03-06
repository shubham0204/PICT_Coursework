
async function onReadItemsClick() {
    const result = await fetch( "read_data.php" )
    const json = await result.json()
    items_table = document.querySelector( "#items_table" )
    items_table.innerHTML = `
            <tr>
                <th>ID</th>
                <th>Name</th>
                <th>Quantity</th>
                <th>Price</th>
            </tr>
    `
    for( i = 0 ; i < json.length ; i++ ) {
        row = items_table.insertRow( -1 )
        console.log( json[i] )
        row.insertCell( 0 ).innerHTML = json[i][0]
        row.insertCell( 1 ).innerHTML = json[i][1]
        row.insertCell( 2 ).innerHTML = json[i][2]
        row.insertCell( 3 ).innerHTML = json[i][3]
    }
}