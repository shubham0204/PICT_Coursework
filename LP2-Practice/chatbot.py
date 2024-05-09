
knowledge = {
    "pict": {
        "admission": "Hello!"
    }
}

def search( query , tree ):
    if tree is str:
        print( tree )
    for ( key , subtree ) in tree.items():
        if key in query:
            search(query, tree[key])
            break
    else:
        options = tree.keys()