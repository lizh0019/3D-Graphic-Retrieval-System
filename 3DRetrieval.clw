; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMy3DRetrievalDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "3DRetrieval.h"
LastPage=0

ClassCount=7
Class1=CMy3DRetrievalApp
Class2=CMy3DRetrievalDoc
Class3=CMy3DRetrievalView
Class4=CMainFrame

ResourceCount=5
Resource1=IDD_DIALOG1_Feature (English (U.S.))
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_ABOUTBOX
Class6=CDialogDataBase
Resource4=IDD_MY3DRETRIEVAL_FORM
Class7=CDialogFeatureSelection
Resource5=IDD_Dialog_DataBase (English (U.K.))

[CLS:CMy3DRetrievalApp]
Type=0
HeaderFile=3DRetrieval.h
ImplementationFile=3DRetrieval.cpp
Filter=N

[CLS:CMy3DRetrievalDoc]
Type=0
HeaderFile=3DRetrievalDoc.h
ImplementationFile=3DRetrievalDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CMy3DRetrievalDoc

[CLS:CMy3DRetrievalView]
Type=0
HeaderFile=3DRetrievalView.h
ImplementationFile=3DRetrievalView.cpp
Filter=D
LastObject=IDC_STARTQUERY
BaseClass=CFormView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_DateBase_SelectDataBase




[CLS:CAboutDlg]
Type=0
HeaderFile=3DRetrieval.cpp
ImplementationFile=3DRetrieval.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN3DMODEL
Command2=ID_FILE_OPEN
Command3=ID_File_FeatureEXtracting
Command4=ID_FILE_PRINT
Command5=ID_FILE_PRINT_PREVIEW
Command6=ID_FILE_PRINT_SETUP
Command7=ID_FILE_MRU_FILE1
Command8=ID_APP_EXIT
Command9=ID_DateBase_SelectDataBase
Command10=DataBase_FeatrueExtract
Command11=ID_DateBase_FeatureExtract_D1
Command12=ID_DateBase_FeatureExtract_D3
Command13=ID_DataBase_FeatureExtract_A3
Command14=ID_DataBase_FeatureExtract_MyOwen
Command15=ID_EDIT_UNDO
Command16=ID_EDIT_CUT
Command17=ID_EDIT_COPY
Command18=ID_EDIT_PASTE
Command19=ID_VIEW_TOOLBAR
Command20=ID_VIEW_STATUS_BAR
Command21=ID_APP_ABOUT
CommandCount=21

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_MY3DRETRIEVAL_FORM]
Type=1
Class=CMy3DRetrievalView
ControlCount=41
Control1=IDC_EDIT_ModelNum,edit,1350633600
Control2=IDC_STATIC_RETIEVALMODEL,button,1342177287
Control3=IDC_STATIC_DataBaseRegion,button,1342177287
Control4=IDC_STATIC_RetrievalMethods,button,1342177287
Control5=IDC_EDIT_DataBasePath,edit,1350633600
Control6=IDC_STATIC_DataBasePath,static,1342308352
Control7=IDC_STATIC_NumModel,static,1342308352
Control8=IDC_EDIT_QueryInfor,edit,1352730628
Control9=IDC_STATIC_Query,static,1350566670
Control10=IDC_STATIC_QUERYRESULT,button,1342177287
Control11=IDC_STARTQUERY,button,1342242816
Control12=ID_FILE_DisplaytModel,button,1342242816
Control13=IDC_STATIC_RetrievalResults1,static,1350636302
Control14=IDC_STATIC_RetrievalResults6,static,1350636302
Control15=IDC_STATIC_RetrievalResults2,static,1350636302
Control16=IDC_STATIC_RetrievalResults3,static,1350636302
Control17=IDC_STATIC_RetrievalResults8,static,1350636302
Control18=IDC_STATIC_RetrievalResults4,static,1350636302
Control19=IDC_STATIC_RetrievalResults9,static,1350636302
Control20=IDC_STATIC_RetrievalResults5,static,1350636302
Control21=IDC_STATIC_RetrievalResults10,static,1350636302
Control22=IDC_STATIC_RetrievalResults7,static,1350636302
Control23=IDC_EDIT_RetrievalName1,edit,1350633600
Control24=IDC_EDIT_RetrievalName6,edit,1350633600
Control25=IDC_EDIT_RetrievalName2,edit,1350633600
Control26=IDC_EDIT_RetrievalName7,edit,1350633600
Control27=IDC_EDIT_RetrievalName3,edit,1350633600
Control28=IDC_EDIT_RetrievalName8,edit,1350633600
Control29=IDC_EDIT_RetrievalName4,edit,1350633600
Control30=IDC_EDIT_RetrievalName9,edit,1350633600
Control31=IDC_EDIT_RetrievalName5,edit,1350633600
Control32=IDC_EDIT_RetrievalName10,edit,1350633600
Control33=IDC_STATIC_CURRENTPAGE,static,1342308352
Control34=IDC_EDIT_Page,edit,1350633472
Control35=IDC_PREVIOUSPAGE,button,1342242816
Control36=IDC_NEXTPAGE,button,1342242816
Control37=IDC_Feature_D2,button,1342242816
Control38=IDC_Feature_D1,button,1342242816
Control39=IDC_Feature_D3,button,1342242816
Control40=IDC_Feature_A3,button,1342242816
Control41=IDC_Feature_MyOwen,button,1342242816

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_Dialog_DataBase (English (U.K.))]
Type=1
Class=CDialogDataBase
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_DataBase,edit,1350631552
Control5=IDC_Browes,button,1342242816

[CLS:CDialogDataBase]
Type=0
HeaderFile=DialogDataBase.h
ImplementationFile=DialogDataBase.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_Browes
VirtualFilter=dWC

[DLG:IDD_DIALOG1_Feature (English (U.S.))]
Type=1
Class=CDialogFeatureSelection
ControlCount=24
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC_ShapeFeatures,static,1342242816
Control5=IDC_CHECK2_FeatureSelection,button,1342242819
Control6=IDC_CHECK2_FeatureSelection2,button,1342242819
Control7=IDC_STATIC_OtherFeature,static,1342308352
Control8=IDC_STATIC_WeightSeting,button,1342177287
Control9=IDC_CHECK3_MultFeature,button,1342242819
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC_MultFeature_D1,static,1342308352
Control12=IDC_EDIT6,edit,1350631552
Control13=IDC_STATIC_MultFeature_D2,static,1342308352
Control14=IDC_EDIT7,edit,1350631552
Control15=IDC_STATIC_MultFeaure_D3,static,1342308352
Control16=IDC_EDIT8,edit,1350631552
Control17=IDC_STATIC_MultFeature_A3,static,1342308352
Control18=IDC_EDIT9,edit,1350631552
Control19=IDC_CHECK4_MultFeature,button,1342242819
Control20=IDC_STATIC_MultFeature_BestWeight,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352

[CLS:CDialogFeatureSelection]
Type=0
HeaderFile=DialogFeatureSelection.h
ImplementationFile=DialogFeatureSelection.cpp
BaseClass=CDialog
Filter=D
LastObject=CDialogFeatureSelection

