import pandas as pd
import numpy as np

cols = [
    "age" , "workclass" , "fnlwgt" , 
    "education" , "education-num" , "marital-status" , 
    "occupation" , "relationship" , "race" , "sex" , 
    "capital-gain" , "capital-loss" , "hours-per-week" , 
    "native-country" , "income"
]
ds = pd.read_csv( "dataset/adult.data" , header=None , skipinitialspace=True ) 
ds.columns = cols
ds = ds.astype( { 
    "workclass": 'string' , "education": 'string' , "marital-status": 'string' , "occupation": 'string' , 
    "relationship": 'string' ,
    "race": 'string' , "sex": 'string' , "native-country": 'string' , "income": 'string'
} )
ds[ "workclass" ] = ds[ "workclass" ].astype( 'string' )

print( "Data-types of all columns" )
print( ds.dtypes )

print( "Initial description of numerical columns in the dataset" ) 
print( ds.describe() )

print( "Check for missing values in all columns of the dataset" )
print( ds.isin( [ "?" ] ).sum()  )
