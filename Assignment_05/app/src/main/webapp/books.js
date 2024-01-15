async function displayBooks() {
    const response = await fetch( "http://localhost:8080/app/books" )
    const books = await response.json()

    const table = document.getElementById( "table-books" )
    books.forEach( function( book ) {
        const row = table.insertRow( -1 )
        row.insertCell(0).innerText = book.title
        row.insertCell(1).innerText = book.author
        row.insertCell(2).innerText = book.price
        row.insertCell(3).innerText = book.quantity
    }) 
}
