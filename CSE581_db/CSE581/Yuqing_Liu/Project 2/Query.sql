USE [States MD Urgent Care Center]
GO
/****** Object: Table Center ******/

CREATE TABLE Center
(   CenterID int  NOT NULL,
    CenterName varchar(50)  NOT NULL,
    CenterAddress varchar(50)  NOT NULL,
    CenterPhone int  NOT NULL,
    CenterZipcode int  NOT NULL,
    BusinessHours varchar(50)  NOT NULL,
	 CONSTRAINT PK_Center PRIMARY KEY CLUSTERED (CenterID ASC));
GO

/****** Object: Table Doctor ******/

CREATE TABLE Doctor 
(   DoctorID int  NOT NULL,
    DoctorName varchar(50)  NOT NULL,
    Telephone int  NOT NULL,
    CenterID int  NOT NULL,
    CONSTRAINT Doctor_pk PRIMARY KEY  (DoctorID),
	CONSTRAINT Doctor_fk FOREIGN KEY (CenterID)
	           REFERENCES Center (CenterID) 
	);
GO

/****** Object: Table HealthyHistory ******/

CREATE TABLE HealthHistory 
  ( PatientID int  NOT NULL,
    CheckInDate smalldatetime  NOT NULL,
    CheckOutDate smalldatetime  NOT NULL,
    Symptoms varchar(50)  NOT NULL,
    Diagnostics varchar(50)  NOT NULL,
    CONSTRAINT HealthHistory_pk PRIMARY KEY  (PatientID));
GO

/****** Object: Table Insurance ******/

CREATE TABLE Insurance (
    PatientID int  NOT NULL,
    Company varchar(50)  NOT NULL,
    IssueDate smalldatetime  NOT NULL,
    ExpiryDate smalldatetime  NOT NULL,
    Coverage int  NOT NULL,
    CONSTRAINT Insurance_pk PRIMARY KEY  (PatientID)
);
GO

/****** Object: Table MedicalEquipment ******/

CREATE TABLE MedicalEquipment (
    CenterID int  NOT NULL,
    WardCapacity int  NOT NULL,
    ReagentQuantities int  NOT NULL,
    EquipmentType int  NOT NULL,
    CONSTRAINT MedicalEquipment_pk PRIMARY KEY  (CenterID)
);
GO

/****** Object: Table Patients ******/
CREATE TABLE Patients (
    PatientID int  NOT NULL,
    PatientName varchar(50)  NOT NULL,
    PatientAddress varchar(50)  NOT NULL,
    PhoneNumber int  NOT NULL,
    Zipcode int  NOT NULL,
    Gender varchar(50)  NOT NULL,
    CONSTRAINT Patients_pk PRIMARY KEY  (PatientID)
);
GO

/****** Object: Table Payment ******/
CREATE TABLE Payment (
    PaymentID int  NOT NULL,
    PatientID int  NOT NULL,
    PaymentMethod varchar(50)  NOT NULL,
    PaymentDate smalldatetime  NOT NULL,
    Price money  NOT NULL,
    CONSTRAINT Payment_pk PRIMARY KEY  (PaymentID),
	CONSTRAINT Payment_fk FOREIGN KEY  (PatientID) 
	          REFERENCES Patients(PatientID)
);
GO

/****** Object: Table Report ******/
CREATE TABLE Report (
    TestID int  NOT NULL,
    ReportDate smalldatetime  NOT NULL,
    Fee money  NOT NULL,
    DeliverDate smalldatetime  NOT NULL,
    CONSTRAINT Report_pk PRIMARY KEY  (TestID)
);
GO

/****** Object: Table Invoice ******/

CREATE TABLE Invoice (
    PaymentID int  NOT NULL,
    InvoiceID int  NOT NULL,
    InvoiceDate smalldatetime  NOT NULL,
    InvoiceAddress varchar(50)  NOT NULL,
	InvoiceZipcode int NOT NULL,
    CONSTRAINT Invoice_pk PRIMARY KEY  (PaymentID)
);
GO

/****** Object: Table DrugStorage ******/
CREATE TABLE DrugStorage (
    CenterID int  NOT NULL,
    DrugID int  NOT NULL,
    DrugName varchar(50)  NOT NULL,
    Quantity int  NOT NULL,
    StorageTime smalldatetime  NOT NULL,
    TakeOutTime smalldatetime  NOT NULL,
    CONSTRAINT DrugStorage_pk PRIMARY KEY  (CenterID)
);
GO

/****** Object: Table ProcedureCapacity ******/
CREATE TABLE ProcedureCapcity (
    CenterID int  NOT NULL,
    ProcedureType int  NOT NULL,
    ProcedureCapcity int  NOT NULL,
    TimeUse varchar(50)  NOT NULL,
    CONSTRAINT ProcedureCapcity_pk PRIMARY KEY  (CenterID)
);
GO

/****** Object: Table Tests ******/
DROP TABLE Tests
CREATE TABLE Tests (
    TestID int  NOT NULL,
    TestDate smalldatetime  NOT NULL,
    ReportDate smalldatetime  NOT NULL,
    Result varchar(50)  NOT NULL,
    Cost money  NOT NULL,
    CenterID int  NOT NULL,
    PaymentID int  NOT NULL,
    PatientID int  NOT NULL,
    DoctorID int  NOT NULL,
    CONSTRAINT Tests_pk PRIMARY KEY  (TestID),
	CONSTRAINT Tests_fk_Patients FOREIGN KEY  (PatientID) 
	          REFERENCES Patients(PatientID),
	CONSTRAINT Tests_fk_Center FOREIGN KEY  (CenterID) 
	          REFERENCES Center(CenterID),
	CONSTRAINT Tests_fk_Payment FOREIGN KEY  (PaymentID) 
	          REFERENCES Payment(PaymentID),
	CONSTRAINT Tests_fk_Doctor FOREIGN KEY  (DoctorID) 
	          REFERENCES Doctor(DoctorID)
);
GO

INSERT Insurance (PatientID, Company, IssueDate, ExpiryDate, Coverage) VALUES
(1001, 'MetLife',  '2017-08-01', '2027-08-01', '80%'),
(1002, 'Aig', '2016-06-17', '2026-06-17', '96%'),
(1003, 'Anthem',  '2016-09-15', '2026-09-15', '90%'),
(1004, 'Aig',  '2015-04-25', '2025-04-25', '96%'),
(1005, 'Anthem', '2014-03-22', '2024-03-22', '90%')
GO

INSERT MedicalEquipment(CenterID, WardCapacity, ReagentQuantities, EquipmentType) VALUES
(1, '50', '300', '5'),
(2, '35', '200', '4'),
(3, '20', '150', '3'),
(4, '25', '180', '3'),
(5, '40', '200', '4')
GO

INSERT Center (CenterID, CenterName, CenterAddress, CenterPhone, CenterZipcode, BusinessHours)
VALUES
(1, 'Kass Urgent Center', '915 Sky St', '8052787', '43201', '9AM-11PM'),
(2, 'Maiya Clinic', '176 Victory Ave','8709922', '44185', '8AM-10PM'),
(3, 'CAL Medical Center', '58 Lux St', '1018762', '44109', '8AM-9PM'),
(4, 'Sinhai Clinic', '328  Balmain St', '6782311', '43220', '7AM-5PM'),
(5, 'Syr Clinic', '923 Light Ave', '8782323', '45216', '8AM-12PM')
GO

INSERT Doctor (DoctorID, DoctorName,Telephone, CenterID)
VALUES
(501, 'Tommy', '5182237', 1),
(502, 'Anny', '5352225', 1),
(531, 'Jackie', '6352359', 3),
(503, 'Felix', '7986542', 1),
(524, 'Chris', '6547822', 2),
(546, 'Alice', '8796657', 4),
(559, 'Betty', '5197656', 5),
(534, 'Ivy', '8098212', 3)
GO

INSERT Patients(PatientID, PatientName, PatientAddress, PhoneNumber, Zipcode, Gender)
VALUES
(1001, 'Marry', '87 Olive St', '8709892', '13202','F'),
(1002, 'Edward', '156 Star Ave', '8026754', '15036', 'M'),
(1003, 'Qin', '16 Hugo St', '5894343', '13167','F'),
(1004, 'Kate', '32 Soho St', '7678934', '13229', 'F'),
(1005, 'Laura', '52 Joy Ave', '80342634', '16482','F')
GO

INSERT HealthHistory(PatientID, CheckInDate, CheckOutDate, Symptoms, Diagnostics)
VALUES
(1001,  '2019-08-07', '2019-08-12', 'Headache','Fever'),
(1002,  '2020-06-15','2020-06-17', 'Dizzy', 'Catch a cold'),
(1002,  '2020-07-15','2020-07-19', 'Headache', 'Catch a cold'),
(1003,  '2020-05-05','2020-05-07', 'Vomit', 'Food poisoning'),
(1004,  '2020-03-22','2020-03-23', 'Headache', 'Allergy'),
(1005,  '2020-05-05','2020-05-07', 'bellyache', 'Food poisoning')
GO


INSERT Payment(PaymentID, PatientID, PaymentMethod, PaymentDate,Price)
VALUES
(131, 1001, 'Cash','2020-09-15','133'),
(132, 1002, 'Cash','2020-10-03','251'),
(133, 1003, 'Credit Card','2020-09-05','160'),
(134, 1004, 'Credit Card','2020-11-11','304'),
(135, 1005, 'Cash','2020-10-28','211')
GO
INSERT Payment(PaymentID, PatientID, PaymentMethod, PaymentDate,Price)
VALUES
(136, 1003, 'Credit Card','2020-09-27','165')
GO


INSERT Tests(TestID, CenterID, PaymentID, PatientID, DoctorID, Cost, Result, TestDate, ReportDate)
VALUES
(1,1,131,1001,501,'34', 'negative','2020-09-15','2020-09-17'),
(2,2,132,1002,524,'10', 'positive','2020-10-03','2020-10-04'),
(3,3,133,1003,534,'18', 'negative','2020-09-05','2020-09-08'),
(4,4,134,1004,546,'13', 'negative','2020-11-11','2020-11-12'),
(5,5,135,1005,559,'23', 'negative','2020-10-28','2020-10-30')
GO

INSERT Tests(TestID, CenterID, PaymentID, PatientID, DoctorID, Cost, Result, TestDate, ReportDate)
VALUES
(6,1,136,1003,501,'25', 'positive','2020-9-27','2020-09-30')