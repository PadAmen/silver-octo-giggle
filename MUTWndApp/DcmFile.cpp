#include "StdAfx.h"
#include "DcmFile.h"
#include "StringConvert.h"
DcmFile::DcmFile(void)
{
	m_pfileformat = new DcmFileFormat();
}

DcmFile::~DcmFile(void)
{
	delete m_pfileformat;
}

DcmDataset *DcmFile::GetDcmDataset(){
	if(m_pfileformat == NULL)
		return NULL;
	return m_pfileformat->getDataset();
}

bool DcmFile::SetDcmOtherInfo()//保存dcm图片
{	
	DcmDataset *pDataset = this->GetDcmDataset();
	if(pDataset == NULL) return false;
	
	char uid[100];
	DcmFileFormat fileformat;
	DcmMetaInfo *metainfo =	fileformat.getMetaInfo();
	
	//***meta group***
	//metainfo->putAndInsertString(DCM_FileMetaInformationVersion,	"US DICOM file");	
	metainfo->putAndInsertString(DCM_MediaStorageSOPInstanceUID,	dcmGenerateUniqueIdentifier(uid,SITE_INSTANCE_UID_ROOT));
	//metainfo->putAndInsertString(DCM_MediaStorageSOPClassUID, UID_UltrasoundImageStorage);
	//metainfo->putAndInsertString(DCM_TransferSyntaxUID,	 	UID_LittleEndianExplicitTransferSyntax);
	//metainfo->putAndInsertString(DCM_ImplementationClassUID, "999.9999");	

	//SOP common module
	//pDataset->putAndInsertString(DCM_SpecificCharacterSet,"ISO_IR 100");
	//pDataset->putAndInsertString(DCM_HL7StructuredDocumentReferenceSequence,"HL7");
	//pDataset->putAndInsertString(DCM_EncryptedAttributesSequence,"encry");

	//***identifying group***
	pDataset->putAndInsertString(DCM_ImageType, "ORIGINAL\\PRIMARY\\TEE\\0011");
	//pDataset->putAndInsertString(DCM_SOPClassUID, UID_UltrasoundImageStorage);//UID_SecondaryCaptureImageStorage);
	//pDataset->putAndInsertString(DCM_SOPInstanceUID,	dcmGenerateUniqueIdentifier(uid, SITE_INSTANCE_UID_ROOT));
	pDataset->putAndInsertString(DCM_StudyID,"398474");
	pDataset->putAndInsertString(DCM_StudyDate,"20100823");
	pDataset->putAndInsertString(DCM_StudyTime,"080322");
	pDataset->putAndInsertString(DCM_Modality,"US");//OT

	pDataset->putAndInsertString(DCM_Manufacturer,"chengdu ultimedical product");
	pDataset->putAndInsertString(DCM_ReferringPhysiciansName,"ANONY");
	pDataset->putAndInsertString(DCM_StudyDescription,"STUDY description");
	pDataset->putAndInsertString(DCM_SeriesDescription,"SERIES DESCRIPTION");
	pDataset->putAndInsertString(DCM_StageNumber,"1");
	pDataset->putAndInsertString(DCM_NumberOfStages,"1");
	pDataset->putAndInsertString(DCM_ViewNumber,"1");
	pDataset->putAndInsertString(DCM_NumberOfViewsInStage,"1");

	

	//*********************************************************************
	// acquisiton group                                                                     
	//***********************************************************************
	//DCM_ProtocolName
	//************************************************************************
	// relation group                                                                    
	//************************************************************************
	pDataset->putAndInsertString(DCM_StudyInstanceUID,"999.999.2.19941105.112000");
	pDataset->putAndInsertString(DCM_SeriesInstanceUID,"999.999.2.19941105.112000.2");
	pDataset->putAndInsertString(DCM_SeriesNumber,"2");
	pDataset->putAndInsertString(DCM_AccessionNumber,"1");
	pDataset->putAndInsertString(DCM_InstanceNumber,"1");
	pDataset->putAndInsertString(DCM_PatientOrientation,"F\\L");
	const int nbitcount = 8;
	return true;
}

	//***patient group****
	//*pDataset->putAndInsertString(DCM_PatientID, this->strPatientID);



bool DcmFile::SetImageInfo(WORD width, WORD height, WORD channel, WORD depth)
{
	DcmDataset *pDataset = this->GetDcmDataset();
	if(pDataset == NULL) return false;
	if(channel != 1 && channel!=3) return false;
	pDataset->putAndInsertString(DCM_PhotometricInterpretation, channel > 1 ? "RGB" : "PALETTE COLOR");	
	if(channel > 1){
		pDataset->putAndInsertUint16(DCM_PlanarConfiguration, 0);//默认使用rgb,rgb,..
	}
	pDataset->putAndInsertUint16(DCM_SamplesPerPixel, channel);
	pDataset->putAndInsertUint16(DCM_BitsAllocated, depth);
	pDataset->putAndInsertUint16(DCM_BitsStored, depth);
	pDataset->putAndInsertUint16(DCM_HighBit, depth-1);
	pDataset->putAndInsertUint16(DCM_PixelRepresentation,0);//是否为有符号数
	pDataset->putAndInsertUint16(DCM_Rows,	height);
	pDataset->putAndInsertUint16(DCM_Columns, width);
	return true;
}
bool DcmFile::Load(LPCTSTR lpszPath)
{
	string str;
	if(!TcharToAnsi(lpszPath, str)) return false;
	if(!this->m_pfileformat->loadFile(str.c_str()).good()){
		return false;
	}else{
		return (m_pfileformat->getDataset()!=NULL);
	}
}
bool DcmFile::Create()
{
	if(m_pfileformat->getDataset() == NULL)
	{
		char uid[100];
	DcmFileFormat fileformat;
	DcmMetaInfo *metainfo =	fileformat.getMetaInfo();

	//***meta group***
	metainfo->putAndInsertString(DCM_FileMetaInformationVersion,	"US DICOM file");	
	metainfo->putAndInsertString(DCM_MediaStorageSOPInstanceUID,	dcmGenerateUniqueIdentifier(uid,SITE_INSTANCE_UID_ROOT));
	metainfo->putAndInsertString(DCM_MediaStorageSOPClassUID, UID_UltrasoundImageStorage);
	metainfo->putAndInsertString(DCM_TransferSyntaxUID,	 	UID_LittleEndianExplicitTransferSyntax);
	metainfo->putAndInsertString(DCM_ImplementationClassUID, "999.9999");	
	return m_pfileformat->append(new DcmDataset()).good();
	}
	return true;
}
bool DcmFile::Save(LPCTSTR lpszPath)
{
	string str;
	if(!TcharToAnsi(lpszPath, str)) return false;
	OFCondition status =  m_pfileformat->saveFile(str.c_str(),	EXS_LittleEndianExplicit);
	return status.good();
}
