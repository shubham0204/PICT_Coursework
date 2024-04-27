# Data Science and Big Data Analytics

## Snippets

### 1. Assigning columns to a dataframe

```python
cols = [
    "age" , "workclass" , "fnlwgt" , 
    "education" , "education-num" , "marital-status" 
]
ds.columns = cols
```

### 2. Dataframe details

```python
ds.dtypes
ds.shape
ds.describe()
```

### 3. Categorical encoding for a feature

```python
def categorical_encoding( feature ):
    global ds
    values = ds[ feature ].unique().tolist()
    for i , val in enumerate( values ):
        ds.loc[ ds[ feature ] == val , feature ] = i
    ds[feature] = ds[feature].astype( 'int32' )

categorical_encoding( "race" )
```

### 4. Min-max normalization for a feature

```python
def min_max_normalize( name ):
    global ds
    ds[name] = ds[name].astype( 'float32' )
    ds[ name ] = (ds[ name ] - ds[ name ].min()) / ( ds[ name ].max() - ds[ name ].min() )
```

### 5. Changing data-type of columns

```python
# Change dtypes from `object` to `str`
ds = ds.astype( { 
    "workclass": 'string' , "education": 'string' , "marital-status": 'string' , "occupation": 'string' , 
    "relationship": 'string' ,
    "race": 'string' , "sex": 'string' , "native-country": 'string' , "income": 'string'
} )
ds.head()
```