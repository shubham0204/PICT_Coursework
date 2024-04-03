# Building a chatbot with hiearchical text-search

search_tree = {
    "admission": {
        "cutoff": "The cuttoff for is > 99 percentile for MHTCET. For more info, refer https://pict.edu/cutoff-FE/",
        "fee": "The fees is 93K for open-category candidates. For more info, refer https://pict.edu/fee-structure/",
        "branch": "Branches are COMP, IT, EnTC, ECE, AIDS",
    },
    "hostel": "The campus has a girls and boys hostel in-premises. For more info, refer https://pict.edu/hostel/",
    "placement": {
        "statistic": "For this year, 706 students are placed. For detailed statistics, refer https://pict.edu/placement/index.php#statistics",
        "activit": "https://pict.edu/placement/index.php#trainingactivities",
    },
    "library": "PICT central library being information hub provides access to full text, digital and printed resources to support the scholarly and informational needs of the students, faculty, researchers, and other users.",
    "timetable": "https://pict.edu/time_table_syllabus/",
    "syllabus": "https://pict.edu/time_table_syllabus/",
}


def search(query: str, subtree):
    if type(subtree) == str:
        print(f"Reply: {subtree}")
        return
    children = list(subtree.keys())
    for child in children:
        if child in query:
            search(query, subtree[child])
            break
    else:
        print("Could not understand context, available options are: ")
        print(children)


while True:
    question = input("Enter your query: ")
    search(question, search_tree)
