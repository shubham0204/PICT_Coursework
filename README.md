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

### 6. Renaming columns of a Dataframe

```python
ds = ds.rename( columns={
    "race/ethnicity": "race" , 
    "parental level of education": "parent_edu" , 
    "test preparation course": "course_completed" , 
    "math score": "score_math" , 
    "reading score": "score_reading" , 
    "writing score": "score_writing"
} )
ds.head()
```

### 7. Remove outliers with `1.5 * IQR` Rule

```python
def remove_outliers(feature):
    global ds
    q3 , q1 = np.percentile( ds[feature] , [ 75 , 25 ] )
    iqr = q3 - q1
    ds = ds[ (ds[feature] >= q1 - 1.5 * iqr) & (ds[feature] <= q3 + 1.5 * iqr) ]
    
remove_outliers( "score_writing" )
```