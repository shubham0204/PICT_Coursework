insert into placement_drives(company_name,package,location)
values
( 'imocha' , 20 , 'pune' ) ,
( 'barclays' , 6 , 'pune' ) , 
( 'tracelink' , 50 , 'mumbai' ) , 
( 'mastercard' , 40 , 'bengaluru' ) , 
( 'google' , 30 , 'mumbai' ) ;

insert into training(company_name,fee,training_year)
values
( 'imocha' , 2000 , '2020' ) ,
( 'barclays' , 500 , '2022' ) , 
( 'tracelink' , 350 , '2021' ) , 
( 'mastercard' , 230 , '2019' ) , 
( 'google' , 5000 , '2019' ) ;

insert into students( drive_id , training_id , name , cgpa , branch )
values
( 1 , 2 , 'Shubham Panchal' , 8.7 , 'CE' ),
( 1 , 3 , 'Advait Naik' , 6.2 , 'CE' ),
( 3 , 2 , 'Kaustubh Netke' , 9.0 , 'CE' ),
( 2 , 2 , 'Anish Pawar' , 8.1 , 'IT' ),
( 1 , 4 , 'Manthan Adhav' , 8.1 , 'IT' ),
( 4 , 1 , 'Advait Nagarkar' , 8.0 , 'IT' ),
( 3 , 3 , 'Rana Vanikar' , 6.8 , 'ENTC' ),
( 2 , 5 , 'Suma Meghana' , 7.8 , 'ENTC' ),
( 5 , 5 , 'Chinmay Patil' , 7.9 , 'CE' ),
( 4 , 4 , 'Anushka Joshi' , 7.6 , 'CE' );
