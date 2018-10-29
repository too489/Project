#include <stdio.h>
#include <stdlib.h>
#include "disk.h"
#include "fs.h"
#include<string.h>
#include <unistd.h>
//블럭사이즈 변경됨 64,아이노드 비트맵이랑 블럭 비트맵바뀜
//아이노드 사이즈 64byte ->16byte
//블럭당 아이노드 갯수는 전과 동일하게 4개임 
//short사이즈는 2임 그럼 inode에 size(2),type(2),indexblkPointer(4),dirblkptr[]은 총 2개들고있음
int inodeno;
int blkno;
int indexblkno;
int setblk=0;
int resetblk=0;
FileDescTable* pFileDescTable = NULL; //과제에서 설정한값//init에서 초기화
FileSysInfo* pFileSysInfo;

void PlusFile();
void MinusFile();
void Plusblk();
void Minusblk();
void blkdelete(int blk);
void CreateIndexBlk(int inodeno);
void printBlkBitmap()
{
	printf("print blk_bitmap : \n");
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	DevReadBlock(BLOCK_BITMAP_BLOCK_NUM ,pBuf);
for(int l=0;l<40;l++){
		int sub=128;
printf("[%d ] :",l);
		for(int i=0;i<8;i++)
			{
			int x=(int)pBuf[l]/sub;
			if(x)
				printf("%d",1);
			else
				printf("%d",0);
			pBuf[l]%=sub;
			sub/=2;
		}
		printf("\n");
	}printf("\n");
}
void printInodeBitmap()
{
	printf("print Ino_bitmap :\n ");
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	DevReadBlock(INODE_BITMAP_BLOCK_NUM ,pBuf);
for(int l=0;l<40;l++){
printf("[%d ] :",l);
		int sub=128;
		for(int i=0;i<8;i++)
			{
			int x=(int)pBuf[l]/sub;
			if(x)
				printf("%d",1);
			else
				printf("%d",0);
			pBuf[l]%=sub;
			sub/=2;
		}
		printf("\n");
	}printf("\n");
}



void FileSysInit(void)//파일 초기화 시킴
{
	//메인파일에서 sysinfo할당 해줘야될꺼같음 block의 갯수는 (BLOCK_SIZE*8) 그리고 초기화할때
	// 파일 info블럭 불러와서 여기서 초기화 해야될꺼깥은데?근데어떻게?
	DevCreateDisk();// 디스크 생성
	DevOpenDisk();
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1); //calloc받
	int i;
	for(i=0;i<BLOCK_SIZE*8;i++)//block 6개만 할당받았지만 이제 더해야될듯
		DevWriteBlock(i,pBuf);
	pFileDescTable = (FileDescTable *)malloc(sizeof(FileDescTable) * MAX_FD_ENTRY_LEN);//여기다 동적할당 
int index;
for(index=0;index<BLOCK_SIZE;index++)//초기화
{   pFileDescTable->file[index].bUsed=0;   }
	free(pBuf);
}

void SetInodeBitmap(int inodeno)//수정필요없음
{	
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);//Block 사이즈 하나만큼할당
	DevReadBlock(INODE_BITMAP_BLOCK_NUM ,pBuf);//아이노드 비트맵 블럭 넘버를 읽어옴
	pBuf[(int)(inodeno/8)]|=(1<<7-(inodeno%8));//inode num을 /로나누면
	DevWriteBlock(INODE_BITMAP_BLOCK_NUM ,pBuf);
	free(pBuf);
}


void ResetInodeBitmap(int inodeno)//수정필요없음
{

	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	DevReadBlock(INODE_BITMAP_BLOCK_NUM ,pBuf);
	pBuf[(int)(inodeno/8)]&=~(1<<7-(inodeno%8));//!->~ change
	DevWriteBlock(INODE_BITMAP_BLOCK_NUM ,pBuf);
	free(pBuf);
}
//block은 0부터채

void SetBlockBitmap(int blkno)//수정필요없음
{

	//printf("bitmap num %d \n",setblk++);
//printf("bitmap num %d 파일셋팅\n",blkno);
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	DevReadBlock(BLOCK_BITMAP_BLOCK_NUM ,pBuf);
	pBuf[(int)(blkno/8)]|=(1<<(7-(blkno%8)));
	DevWriteBlock(BLOCK_BITMAP_BLOCK_NUM ,pBuf);
	free(pBuf);

}


void ResetBlockBitmap(int blkno)//수정필요없음
{
	//printf("reset bitmap num %d \n",resetblk++);
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	DevReadBlock(BLOCK_BITMAP_BLOCK_NUM ,pBuf);
	pBuf[(int)(blkno/8)]&=~(1<<7-(blkno%8));
	DevWriteBlock(BLOCK_BITMAP_BLOCK_NUM ,pBuf);
	free(pBuf);

}


void PutInode(int inodeno, Inode* pInode) //나름 수정 완료
{
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	Inode InodeList[4];
	DevReadBlock((int)(inodeno/4)+3,pBuf);
	memcpy(InodeList,pBuf, BLOCK_SIZE);
	int inodeindex=0;
	inodeindex=inodeno%4;//64->16으로 수정함 인덱스가 16이니깐
	//printf("풋 인덱스 %d : ",inodeindex);
	//pBuf[inodeindex]=pInode->size;//	pBuf[inodeindex]=pInode->allocBlocks;
	//pBuf[inodeindex+2]=pInode->type;//	pBuf[inodeindex+4]=pInode->type;
	InodeList[inodeindex].size=pInode->size;
	InodeList[inodeindex].type=pInode->type;
	for(int i=0;i<2;i++)
		InodeList[inodeindex].dirBlockPtr[i]=pInode->dirBlockPtr[i];
		//pBuf[inodeindex+i*4]=pInode->dirBlockPtr[i-1];
//printf("집어넣는거아이노드 블럭 넘버 : %d \n",pBuf[inodeindex+1*4]);
	//pBuf[inodeindex+12]=pInode->indirBlockPtr;
	InodeList[inodeindex].indirBlockPtr=pInode->indirBlockPtr;
	memcpy(pBuf,InodeList, BLOCK_SIZE);
	DevWriteBlock((int)(inodeno/4)+3,pBuf);
//	printf("%d",pBuf[inodeindex+1*4]);


	free(pBuf);

}

void GetInode(int inodeno, Inode* pInode)
{
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	Inode InodeList[4];
	DevReadBlock((inodeno/4)+3,pBuf);
	memcpy(InodeList,pBuf, BLOCK_SIZE);
	int inodeindex=0;
	inodeindex=inodeno%4;
	pInode->size=InodeList[inodeindex].size;
	pInode->type=InodeList[inodeindex].type;

	for(int i=0;i<2;i++)
		pInode->dirBlockPtr[i]=InodeList[inodeindex].dirBlockPtr[i];

	pInode->indirBlockPtr=InodeList[inodeindex].indirBlockPtr;

	//free(pBuf);

}


int GetFreeInodeNum(void)//수정완료
{
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	DevReadBlock(INODE_BITMAP_BLOCK_NUM ,pBuf);
	for(int l=0;l<BLOCK_SIZE;l++){//왜 그전에 64로 했을까 512로 안하고
		int sub=128;
		for(int i=0;i<8;i++)
			{
			int x=(int)pBuf[l]/sub;
			if(!x){
				return l*8+i;
				}
			pBuf[l]%=sub;
			sub/=2;
		}
	}
	free(pBuf);
}


int GetFreeBlockNum(void)//수정완료   
{

	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	DevReadBlock(BLOCK_BITMAP_BLOCK_NUM ,pBuf);
	for(int l=0;l<BLOCK_SIZE;l++){
		int sub=128;
		for(int i=0;i<8;i++)
			{
			int x=(int)pBuf[l]/sub;
			if(!x){
				return l*8+i;
				}
			pBuf[l]%=sub;
			sub/=2;
		}
	}
	free(pBuf);
}
//---------------------------두번째 과제 거진 시작점 ----------------------------------//
extern void		Mount(MountType type)
{//타입에 이런게 있따 MT_TYPE_FORMAT=0//initialize해주는 flag,MT_TYPE_READWRITE=1//다시 읽고쓰는 flag

	if(type==0)
	{
		FileSysInit();//block에 512개에 0으로 넣어주는거 완료(초기화)
		
		//파일 18번까지 setblock
		for(int i =0 ; i<=18;i++)
		{
			SetBlockBitmap(i);
		}
		//아이노드 다이렉토리 셋팅
		unsigned char *pBuf = (unsigned char *)calloc(BLOCK_SIZE, 1);
//
		DirEntry diren[NUM_OF_DIRENT_PER_BLOCK];


		inodeno=GetFreeInodeNum();
		blkno=GetFreeBlockNum();
		SetInodeBitmap(inodeno);
		SetBlockBitmap(blkno);
	//	printf("정말 초기화 blk,%d ",blkno);
		memset(diren,0,BLOCK_SIZE);
		strcpy(diren[0].name,".");
		diren[0].inodeNum=inodeno;//새로운 아이노드 설정 및 등록


		memset(pBuf, 0, BLOCK_SIZE);
		memcpy(pBuf, diren, BLOCK_SIZE);
		DevWriteBlock(blkno,pBuf);//이제 저장된 root블럭쓰기
//		SetBlockBitmap(blkno);
		//free(pBuf);
		pFileSysInfo=malloc(BLOCK_SIZE);
	//---------------블럭0번 info부분 초기화
		int Ibuf[BLOCK_SIZE/sizeof(int)];
		//
		pFileSysInfo->blocks=FS_DISK_CAPACITY/BLOCK_SIZE;
		pFileSysInfo->rootInodeNum = INODELIST_BLOCK_FIRST;
		pFileSysInfo->diskCapacity=FS_DISK_CAPACITY;
		pFileSysInfo->numAllocBlocks=19;//할당된 갯
		pFileSysInfo->numFreeBlocks=493;//할당되지않은 블럭개수//바로할당?
		pFileSysInfo->numAllocInodes=0;//할당된 inode의 개수 -현재 할당된  아이노드 갯수는 할당된 파일의갯
		pFileSysInfo->blockBitmapBlock=BLOCK_BITMAP_BLOCK_NUM;//
		pFileSysInfo->inodeBitmapBlock=INODE_BITMAP_BLOCK_NUM;
		pFileSysInfo->inodeListBlock=INODELIST_BLOCK_FIRST;
		pFileSysInfo->dataRegionBlock =19;

//--------------블럭 0번 info초기화 종료//

//----------root디렉토리의  아이노드를 획득후 block포인터변경

		Inode *pInode=(Inode *)calloc(BLOCK_SIZE/4,1);
		//GetInode(0,pInode);//처음만들때 블럭하나만들어서
		pInode->dirBlockPtr[0]=19;
		pInode->dirBlockPtr[1]=255;
		pInode->indirBlockPtr=255;// 폴더 만들때 1번 다이렉트랑 인다이렉트 -1 입력
		pInode->size=64;//4개 다 넣었기 때문

		pInode->type=1;
		PutInode(0,pInode);
		//block과 아이노드 넘버 재정
		pFileSysInfo->numAllocBlocks=20;
		pFileSysInfo->numFreeBlocks=492;
		pFileSysInfo->numAllocInodes=1;

		memset(pBuf, 0, BLOCK_SIZE);
	//	memcpy(fn, pFileSysInfo, BLOCK_SIZE);
		DevWriteBlock(FILESYS_INFO_BLOCK,(char *)pFileSysInfo);

	}
	else
	{
		DevOpenDisk();
		pFileDescTable = calloc((sizeof(FileDescTable) * MAX_FD_ENTRY_LEN),1);//여기다 동적할당

	}
}
extern void		Unmount(void)
{
	DevCloseDisk();
}

int		OpenFile(const char* szFileName, OpenFlag flag)
{
	//반드시성공

	char strstr[50];char buf[60]; 	char * pch; int k=0;
	unsigned int * indexblk=(unsigned int *)calloc(BLOCK_SIZE,1);
	Inode *pInode=(Inode *)calloc(BLOCK_SIZE/4,1);
	DirEntry diren[NUM_OF_DIRENT_PER_BLOCK]; int Is=0;int prevInode =0;
	memset(diren,0,BLOCK_SIZE);
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	char *path[12];
//printInodeBitmap();
	for (int i = 0; i < 12; i++)
		path[i] = 0;

	strcpy(strstr, szFileName);
//printf("fullpath:  %s\n ",strstr);
	k=0;

	pch = strtok(strstr, "/");
	while (pch != NULL)
	{
		path[k]=pch;
		pch = strtok(NULL, "/");
		k++;
	}//i는 경로들의 갯수 // path[i]로 하나씩 빼서쓰면 

//printf("%s파일  생성 ,inode :%d \n",path[k-1],inodeno);
		inodeno=0;
	//	strcpy(prevInode,dir.inodeNum);
		for(int count=0;count<k-1;count++){Is=0;
			for(int ptr=0;ptr<NUM_OF_DIRECT_BLOCK_PTR;ptr++)
				{
				memset(pInode,255,sizeof(Inode));
				GetInode(inodeno,pInode);
				blkno=pInode->dirBlockPtr[ptr];
				memset(pBuf,0,BLOCK_SIZE);
				memset(diren, 0, BLOCK_SIZE);
				DevReadBlock(blkno,pBuf);
				memcpy(diren, pBuf, BLOCK_SIZE);
			for (int i=0;i<4;i++)
				{
				//	printf("출력전 이름 출력 [%s ? %s ] 블럭 %d \n",diren[i].name,path[count],blkno);
					if(!strcmp(diren[i].name,path[count]))
						{
							inodeno=diren[i].inodeNum;
							Is=1;
							break;
						}
				}
				if(Is)
				break;
			}

			if(!Is)
			{
				memset(pInode,255,sizeof(Inode));
				GetInode(inodeno,pInode);
				indexblkno=pInode->indirBlockPtr;
				//printf("인다이렉트 블럭? %d\n",indexblkno);
				DevReadBlock(indexblkno ,pBuf);
				memcpy(indexblk,pBuf,BLOCK_SIZE);//인다이렉트블록들을 배열로 하나하나 접속한다 단 i번째부터 쭉쭉
				for(int i=0;i<BLOCK_SIZE/sizeof(int);i++){
					blkno=indexblk[i];
					memset(pBuf,0,BLOCK_SIZE);
					DevReadBlock(blkno ,pBuf);
					memcpy(diren, pBuf, BLOCK_SIZE);
					for(int l=0;l<4;l++){
			//		printf("indirect 출력전 이름 출력 [%s ? %s ] 블럭 %d \n",diren[l].name,path[count],blkno);
					if(!strcmp(diren[l].name,path[count]))
					{
						inodeno=diren[l].inodeNum;
					//	printf("여기는?");
						break;
					}
					}Is=1;
					break;
				}
			}
		}
		//printf("오픈할때 시작 아이노드%d!!!!!!!!\n",inodeno);

//COUNT FOR문 종료
	//작업하기 전까지의 path 획득
		for(int ptr=0;ptr<NUM_OF_DIRECT_BLOCK_PTR;ptr++){
			memset(diren,0,BLOCK_SIZE);
			memset(pInode,255,sizeof(Inode));
			GetInode(inodeno,pInode);
			if(pInode->dirBlockPtr[ptr]==255)
			{
				blkno=GetFreeBlockNum();
				SetBlockBitmap(blkno);
				Plusblk();
				pInode->dirBlockPtr[ptr]=blkno;
			}
			blkno=pInode->dirBlockPtr[ptr];
			DevReadBlock(blkno,pBuf);
			memcpy(diren, pBuf, BLOCK_SIZE);//여기까지했음
			//printf("다이렉트에서 불러온 블럭 : %d\n",blkno);

			for (int i=0;i<4;i++)
			{
				//printf("[%s ? %s]파일 오픈시 비교  , blk : %d \n",path[k-1],diren[i].name,blkno);
			if(flag){
				//	printf("[%s ? %s]파일 생성?  ,fd :%d , blk : %d \n",path[k-1],diren[i].name,i,blkno);
					if(!strcmp(diren[i].name,""))
					{
		//			printf("상위 다이렉트 [%d]블럭 ,direct[%d]\n",ptr,blkno);
					PutInode(inodeno,pInode);
					prevInode=inodeno;
					inodeno=GetFreeInodeNum();
					SetInodeBitmap(inodeno);
					strcpy(diren[i].name,path[k-1]);
					diren[i].inodeNum=inodeno;
				//	printf("파일 생성시 아이노드 %d\n",diren[i].inodeNum);
					memset(pBuf, 0, BLOCK_SIZE);
					memcpy(pBuf, diren, BLOCK_SIZE);
					memset(diren,0,BLOCK_SIZE);
					DevWriteBlock(blkno ,pBuf);//inode에 비어있는 블록넘버의 블록 셋팅
					memset(pInode,255,sizeof(Inode));
					GetInode(inodeno,pInode);
					pInode->size=0;//아직 크기가 0
					pInode->type=0;//dir타입
					blkno=GetFreeBlockNum();
					SetBlockBitmap(blkno);
					Plusblk();
					pInode->dirBlockPtr[0]=blkno;
	//		printf("%s파일 생성 성공 ,inode :%d , blk : %d \n",path[k-1],inodeno,blkno);
					pInode->dirBlockPtr[1]=255;
					pInode->indirBlockPtr=255;
					PutInode(inodeno,pInode);
					PlusFile();

				//	printf("%s파일 생성 성공 ,inode :%d , blk : %d \n",path[k-1],inodeno,blkno);
					for(i=0;i<MAX_FD_ENTRY_LEN;i++)
							if(pFileDescTable->file[i].bUsed==0)
							{
								pFileDescTable->file[i].inodeNum=inodeno;
								//printf("create inode no : %d\n",inodeno);
								pFileDescTable->file[i].bUsed=1;
								pFileDescTable->file[i].fileOffset=0;

								return i;
							}
						Is=1;
						}
					}
				else //다이렉트블럭에서 파일찾기
				{
					//printf("[%s ? %s]파일 읽기 성공  ,inodeno:%d , blk : %d \n",diren[i].name,path[k-1],diren[i].inodeNum,blkno);
					if(!strcmp(diren[i].name,path[k-1]))
					{	for(int l=0;l<MAX_FD_ENTRY_LEN;l++)
							if(pFileDescTable->file[l].bUsed==0)
							{
								//printf("[%s ? %s]파일 읽기 성공  ,fd :%d , blk : %d \n",diren[i].name,path[k-1],i,blkno);
								pFileDescTable->file[l].inodeNum=diren[i].inodeNum;
							//	printf("읽을때 inode no : %d,이름?%s\n",diren[i].inodeNum,diren[i].name);
								pFileDescTable->file[l].bUsed=1;
								pFileDescTable->file[l].fileOffset=0;
								//print인f("%s파일 생성 성공 ,fd :%d , blk : %d \n",path[k-1],i,blkno);
								return l;
							}
					}
				}
			}
		}
	//없으면 파일생성 이게 안되면 indirectblockd으로
			if(pInode->indirBlockPtr==255)
			{
				//만약 없으면 생성하기
				indexblkno=GetFreeBlockNum();
				SetBlockBitmap(indexblkno);//이 블록은 인다이렉트 인덱스 블록
				Plusblk();
				pInode->indirBlockPtr=indexblkno;
				PutInode(inodeno,pInode);
				memset(pBuf,0,BLOCK_SIZE);//인다이렉트 블럭으로 넘어가는 함수 설정해야됨 없으면 생성
				for(int i=0;i<BLOCK_SIZE;i++)//인덱스블록 초기화
					indexblk[i]=0;
				memcpy(pBuf,indexblk,BLOCK_SIZE);
				DevWriteBlock(indexblkno,pBuf);

				}
			else
				indexblkno=pInode->indirBlockPtr;

			DevReadBlock(indexblkno ,pBuf);
			memcpy(indexblk,pBuf,BLOCK_SIZE);
		for(int i=0;i<BLOCK_SIZE/sizeof(int);i++)
			{
				memset(pBuf,0,BLOCK_SIZE);
				if(flag){
					if(indexblk[i]==0){
						blkno=GetFreeBlockNum();
						indexblk[i]=blkno;
						SetBlockBitmap(blkno);
						Plusblk();
						memcpy(pBuf, indexblk, BLOCK_SIZE);
						DevWriteBlock(indexblkno,pBuf);
						memset(indexblk,0,BLOCK_SIZE);
						DevReadBlock(indexblkno ,pBuf);
						memcpy(indexblk,pBuf,BLOCK_SIZE);
						}
					}
				blkno=indexblk[i];
			//	printf("indexblk : %d\n",blkno);
				DevReadBlock(blkno ,pBuf);
				memcpy(diren, pBuf, BLOCK_SIZE);


				for (int l=0;l<4;l++)
				{
				//	printf("인 다이렉트에서 불러온 블럭 : %d\n",blkno);
				if(flag){
					if(!strcmp(diren[l].name,""))
					{
//printf("****상위 인다이렉트 인덱스 블럭번호 blk : [%d]  \n",blkno);
						prevInode=inodeno;//".."에 넣을값
						inodeno=GetFreeInodeNum();

						SetInodeBitmap(inodeno);
						memset(pBuf,0,BLOCK_SIZE);

						strcpy(diren[l].name,path[k-1]);
						diren[l].inodeNum=inodeno;
						memcpy(pBuf, diren, BLOCK_SIZE);
						memset(diren,0,BLOCK_SIZE);
						DevWriteBlock(blkno ,pBuf);
						memset(pInode,255,sizeof(Inode));
						GetInode(inodeno,pInode);
						pInode->size=0;//아직 크기가 0
						pInode->type=0;//filetype
			//printf("%s파일 생성 성공 왜 ???blk가 0이야,inode :%d , blk : %d \n",path[k-1],inodeno,blkno);
						blkno=GetFreeBlockNum();
						blkno=GetFreeBlockNum();
		//	printf("%s파일 생성 성공 왜 ???blk가 0이야,inode :%d , blk : %d \n",path[k-1],inodeno,blkno);
						SetBlockBitmap(blkno);
						Plusblk();
						pInode->dirBlockPtr[0]=blkno;

						pInode->dirBlockPtr[1]=255;
						pInode->indirBlockPtr=255;
						PutInode(inodeno,pInode);//한번뿐이잖
						PlusFile();
//printf("****%s파일 생성 성공 ,inode :%d , blk : %d ,dir:indirect[%d], indexblk[%d]\n",path[k-1],inodeno,blkno,indexblkno,indexblk[i]);
						for(i=0;i<MAX_FD_ENTRY_LEN;i++)
						if(pFileDescTable->file[i].bUsed==0)
						{
							pFileDescTable->file[i].inodeNum=inodeno;
							pFileDescTable->file[i].bUsed=1;
							pFileDescTable->file[i].fileOffset=0;
																				
							memset(pBuf, 0, BLOCK_SIZE);
							DevWriteBlock(blkno ,pBuf);
							return i;
						}
					 }
					}
					else //다이렉트블럭에서 파일찾기
					{
						//printf("[%s ? %s]파일 읽기 성공  ,inode :%d , blk : %d \n",diren[l].name,path[k-1],inodeno,blkno);
					if(!strcmp(diren[l].name,path[k-1]))
						for(i=0;i<MAX_FD_ENTRY_LEN;i++)
							if(pFileDescTable->file[i].bUsed==0)
							{
								//printf("[%s ? %s]파일 읽기 성공 ,fd :%d , blk : %d \n",diren[i].name,path[k-1],i,blkno);
								pFileDescTable->file[i].inodeNum=diren[l].inodeNum;
								pFileDescTable->file[i].bUsed=1;
								pFileDescTable->file[i].fileOffset=0;
								return i;
							}
					}
				}//for문
			}
		
return -1;

}

int		WriteFile(int fileDesc, char* pBuffer, int length)
{

	unsigned int * indexblk=(unsigned int *)calloc(BLOCK_SIZE,1);
	Inode *pInode=(Inode *)calloc(BLOCK_SIZE/4,1);
	DirEntry diren[NUM_OF_DIRENT_PER_BLOCK];
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	int prevInode =0;
	int Offset=0;

	//printf(" 파일 쓰기중 fd: %d pbuffer %s,length %d.\n",fileDesc,pBuffer,length);

	double times=(double)length/BLOCK_SIZE;
	inodeno=pFileDescTable->file[fileDesc].inodeNum;
	GetInode(inodeno,pInode);
	for(int c=0;c<times;c++){
//	printf("time : %f \n", times);
//	printf("%d : offset \n",pFileDescTable->file[fileDesc].fileOffset);

	//printf("%d : inode \n",inodeno);
	Offset=pFileDescTable->file[fileDesc].fileOffset/BLOCK_SIZE;//블럭크기의 순서1,2
//printf("offset ?? %d\n",Offset);
		if(Offset==0){
			pFileDescTable->file[fileDesc].fileOffset+=BLOCK_SIZE;
		//	printf("여기의 블럭넘버??잇냐???%d\n",pInode->dirBlockPtr[0]);
			blkno=pInode->dirBlockPtr[0];
		//	printf("1 : write ?? %d\n",Offset);
			memset(pBuf,0,BLOCK_SIZE);
			memcpy(pBuf,pBuffer,BLOCK_SIZE);
			DevWriteBlock(blkno ,pBuf);
			pInode->size+=length;
			PutInode(inodeno,pInode);
			}
		else if(Offset==1){
			if(pInode->dirBlockPtr[1]==255){
			blkno=GetFreeBlockNum();//추가했네?? 왜??
			SetBlockBitmap(blkno);
			Plusblk();
			pInode->dirBlockPtr[1]=blkno;
			}
			blkno=pInode->dirBlockPtr[1];
			memset(pBuf,0,BLOCK_SIZE);
			memcpy(pBuf,pBuffer,BLOCK_SIZE);
			DevWriteBlock(blkno ,pBuf);
			pFileDescTable->file[fileDesc].fileOffset+=BLOCK_SIZE;
			pInode->size=pInode->size+length;
			PutInode(inodeno,pInode);
		//	printf("2 : write ?? %d\n",Offset);
			}

		else
		{
			if(pInode->indirBlockPtr==255){
			indexblkno=GetFreeBlockNum();//추가했네?? 왜??
			SetBlockBitmap(indexblkno);
			Plusblk();

			pInode->indirBlockPtr=indexblkno;
			PutInode(inodeno,pInode);
			}else
			indexblkno=pInode->indirBlockPtr;

			memset(indexblk,0,BLOCK_SIZE);
			memset(pBuf,0,BLOCK_SIZE);//인다이렉트 블럭으로 넘어가는 함수
			DevReadBlock(indexblkno ,pBuf);
			memcpy(indexblk,pBuf,BLOCK_SIZE);

			//if(indexblk[Offset-2]==0)
			//{
		//	printf("여기서 할당못받나?? 1 [%d]\n",blkno);
			blkno=GetFreeBlockNum();
			//printf("여기서 할당못받나?? 2 [%d]\n",blkno);

			indexblk[Offset-2]=blkno;
		//	printf("indexblk?? %d\n",indexblk[Offset-2]);
			SetBlockBitmap(blkno);
			Plusblk();
			memset(pBuf,0,BLOCK_SIZE);//인다이렉트 블럭으로 넘어가는 함수
			memcpy(pBuf,indexblk,BLOCK_SIZE);
			DevWriteBlock(indexblkno ,pBuf);
			//}
			//else
				blkno=indexblk[Offset-2];

			pFileDescTable->file[fileDesc].fileOffset+=BLOCK_SIZE;
			memset(pBuf,0,BLOCK_SIZE);
			memcpy(pBuf,pBuffer,BLOCK_SIZE);
			DevWriteBlock(blkno ,pBuf);


			pInode->size+=length;
			PutInode(inodeno,pInode);
			//printf("3 : write ?? %d한사이클 종료\n",Offset);
//printBlkBitmap();

		}
	}	
	return length;
//free(indexblk);
//free(pBuf);
//free(pInode);
}

int		ReadFile(int fileDesc, char* pBuffer, int length)
{

	unsigned int * indexblk=(unsigned int *)calloc(BLOCK_SIZE,1);
	Inode *pInode=(Inode *)calloc(BLOCK_SIZE/4,1);
	DirEntry diren[NUM_OF_DIRENT_PER_BLOCK];
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	int prevInode =0;
	int Offset=0;

	Offset=pFileDescTable->file[fileDesc].fileOffset/BLOCK_SIZE;//블럭크기의 순서1,2
	inodeno=pFileDescTable->file[fileDesc].inodeNum;
	GetInode(inodeno,pInode);
//	printf("offset? %d\n",Offset);
//	printf("inodeno? %d\n",inodeno);

	if(Offset==0){
				pFileDescTable->file[fileDesc].fileOffset+=BLOCK_SIZE;
				blkno=pInode->dirBlockPtr[0];
	//			printf("blkno %d\n",blkno);
				DevReadBlock(blkno ,pBuffer);
				//for(int i=0;i<BLOCK_SIZE;i++)
		//		printf("%s\n",pBuffer);
	//			printf("읽기???????????%s''''''''''''''''''\n",pBuffer);


				return length;
				}
			else if(Offset==1){
				if(pInode->dirBlockPtr[1]==255){
					return -1;
				}
				blkno=pInode->dirBlockPtr[1];
				DevReadBlock(blkno ,pBuffer);
	//			printf("읽기222222 %s\n",pBuffer);
				//fflush(stdout);
				pFileDescTable->file[fileDesc].fileOffset+=BLOCK_SIZE;
				return length;
				}

			else
			{
				if(pInode->indirBlockPtr==255){return -1;
				}else
				indexblkno=pInode->indirBlockPtr;
				//printf("indexblk?? %d\n",indexblkno);
				memset(indexblk,0,BLOCK_SIZE);
				memset(pBuf,0,BLOCK_SIZE);//인다이렉트 블럭으로 넘어가는 함수
				DevReadBlock(indexblkno ,pBuf);

				memcpy(indexblk,pBuf,BLOCK_SIZE);
				blkno=indexblk[Offset-2];
	//			printf("indexblk?? %d\n",indexblk[Offset-2]);
				pFileDescTable->file[fileDesc].fileOffset+=BLOCK_SIZE;
	//			printf("blkno?? %d\n",blkno);
				DevReadBlock(blkno ,pBuffer);
	//			printf("읽기%s\n",pBuffer);

				return length;

			}


}


int		CloseFile(int fileDesc)
{

	pFileDescTable->file[fileDesc].bUsed=0;
	pFileDescTable->file[fileDesc].inodeNum=0;
	pFileDescTable->file[fileDesc].fileOffset=0;
	//printf("fd %d 번째 닫기 성공\n",fileDesc);
}

int		RemoveFile(const char* szFileName)
{
	char strstr[50];char buf[60]; 	char * pch; int k=0;int c=0;int p=0;
	unsigned int * indexblk=(unsigned int *)calloc(BLOCK_SIZE,1);
	Inode *pInode=(Inode *)calloc(BLOCK_SIZE/4,1);
	DirEntry diren[NUM_OF_DIRENT_PER_BLOCK]; int Is=0;int prevInode =0;
	memset(diren,0,BLOCK_SIZE);
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	char *path[12];
//printInodeBitmap();
	for (int i = 0; i < 12; i++)
		path[i] = 0;

	strcpy(strstr, szFileName);
//printf("fullpath:  %s\n ",strstr);
	k=0;

	pch = strtok(strstr, "/");
	while (pch != NULL)
	{
		path[k]=pch;
		pch = strtok(NULL, "/");
		k++;
	}//i는 경로들의 갯수 // path[i]로 하나씩 빼서쓰면


		inodeno=0;
	//	strcpy(prevInode,dir.inodeNum);
		for(int count=0;count<k-1;count++){Is=0;
			for(int ptr=0;ptr<NUM_OF_DIRECT_BLOCK_PTR;ptr++)
				{
				memset(pInode,255,sizeof(Inode));
				GetInode(inodeno,pInode);
				blkno=pInode->dirBlockPtr[ptr];
				memset(pBuf,0,BLOCK_SIZE);
				memset(diren, 0, BLOCK_SIZE);
				DevReadBlock(blkno,pBuf);
				memcpy(diren, pBuf, BLOCK_SIZE);
			for (int i=0;i<4;i++)
				{
				//	printf("출력전 이름 출력 [%s ? %s ] 블럭 %d \n",diren[i].name,path[count],blkno);
					if(!strcmp(diren[i].name,path[count]))
						{
							inodeno=diren[i].inodeNum;
							Is=1;
							break;
						}
				}
				if(Is)
				break;
			}

			if(!Is)
			{
				memset(pInode,255,sizeof(Inode));
				GetInode(inodeno,pInode);
				indexblkno=pInode->indirBlockPtr;
				//printf("인다이렉트 블럭? %d\n",indexblkno);
				DevReadBlock(indexblkno ,pBuf);
				memcpy(indexblk,pBuf,BLOCK_SIZE);//인다이렉트블록들을 배열로 하나하나 접속한다 단 i번째부터 쭉쭉
				for(int i=0;i<BLOCK_SIZE/sizeof(int);i++){
					blkno=indexblk[i];
					memset(pBuf,0,BLOCK_SIZE);
					DevReadBlock(blkno ,pBuf);
					memcpy(diren, pBuf, BLOCK_SIZE);
					for(int l=0;l<4;l++){
			//		printf("indirect 출력전 이름 출력 [%s ? %s ] 블럭 %d \n",diren[l].name,path[count],blkno);
					if(!strcmp(diren[l].name,path[count]))
					{
						inodeno=diren[l].inodeNum;
					//	printf("여기는?");
						break;
					}
					}Is=1;
					break;
				}
			}
		}
		//printf("오픈할때 시작 아이노드%d!!!!!!!!\n",inodeno);//COUNT FOR문 종료//맞
	//그럼 inodeg획득했으니 그에 해당하는 block속 =파일생성하기
		for(int ptr=0;ptr<NUM_OF_DIRECT_BLOCK_PTR;ptr++){
			memset(diren,0,BLOCK_SIZE);
			memset(pInode,255,sizeof(Inode));
			GetInode(inodeno,pInode);
			blkno=pInode->dirBlockPtr[ptr];
			DevReadBlock(blkno,pBuf);
			memcpy(diren, pBuf, BLOCK_SIZE);
			prevInode=inodeno;
		for (int i=0;i<4;i++)
		{
			if(!strcmp(diren[i].name,path[k-1]))
			{
			inodeno=diren[i].inodeNum;
			for(p=0;p<sizeof(FileDescTable);p++){
				if(pFileDescTable->file[p].inodeNum==inodeno)
					if(pFileDescTable->file[p].bUsed==1)
						return -1;}
			//printf("열려있으면 닫기 \n");

			strcpy(diren[i].name,"");
			inodeno=diren[i].inodeNum;
			diren[i].inodeNum=255;
			memset(pBuf,0,BLOCK_SIZE);
			memcpy(pBuf,diren,BLOCK_SIZE);
			DevWriteBlock(blkno,pBuf);//전라인 0으로 초기화
			memset(pInode,0,sizeof(Inode));
			GetInode(inodeno,pInode);
			ResetInodeBitmap(inodeno);
			pInode->size=0;
			pInode->type=0;
			blkno=pInode->dirBlockPtr[0];//해당 블럭 삭제및 리셋
			blkdelete(blkno);

			if(pInode->dirBlockPtr[1]!=255){
			blkno=pInode->dirBlockPtr[1];
			blkdelete(blkno);
			pInode->dirBlockPtr[1]=255;
			}
			if(pInode->indirBlockPtr!=255){
			indexblkno=pInode->indirBlockPtr;
			memset(pBuf,0,BLOCK_SIZE);
			DevReadBlock(indexblkno,pBuf);
			memcpy(indexblk,pBuf,BLOCK_SIZE);
			for(c=0;c<BLOCK_SIZE/sizeof(int);c++)
			{
				if(indexblk[c]!=0)
					if(blkno=indexblk[c])
						blkdelete(blkno);
			}
			blkdelete(indexblkno);
			pInode->indirBlockPtr=255;
			}
			pInode->dirBlockPtr[0]=255;


			PutInode(inodeno,pInode);
			//printf("%s 삭제완료 \n",path[k-1]);
			return 0;
			}
		}
	}//다이렉트 까지 삭제 인다이렉트면? 다음으로
	indexblkno=pInode->indirBlockPtr;
	DevReadBlock(indexblkno ,pBuf);
	memcpy(indexblk,pBuf,BLOCK_SIZE);
	memset(pBuf,0,BLOCK_SIZE);
		for(int l=0;l<BLOCK_SIZE/sizeof(int);l++)
		{
			blkno=indexblk[l];
			DevReadBlock(blkno ,pBuf);//불러왔을땐 깨끗한상태
			memcpy(diren, pBuf, BLOCK_SIZE);
			for (int i=0;i<4;i++)
			{
				if(!strcmp(diren[i].name,path[k-1]))
				{
					inodeno=diren[i].inodeNum;
					for(p=0;p<sizeof(FileDescTable);p++){
						if(pFileDescTable->file[p].inodeNum==inodeno)
							if(pFileDescTable->file[p].bUsed==1)
								return -1;}
					//printf("열려있으면 닫기 \n");

					strcpy(diren[i].name,"");
					inodeno=diren[i].inodeNum;
					diren[i].inodeNum=255;
					memset(pBuf,0,BLOCK_SIZE);
					memcpy(pBuf,diren,BLOCK_SIZE);
					DevWriteBlock(blkno,pBuf);//전라인 0으로 초기화
					memset(pInode,0,sizeof(Inode));
					GetInode(inodeno,pInode);
					ResetInodeBitmap(inodeno);
					pInode->size=0;
					pInode->type=0;
					blkno=pInode->dirBlockPtr[0];//해당 블럭 삭제및 리셋
					blkdelete(blkno);

					if(pInode->dirBlockPtr[1]!=255){
					blkno=pInode->dirBlockPtr[1];
					blkdelete(blkno);
					pInode->dirBlockPtr[1]=255;
					}
					if(pInode->indirBlockPtr!=255){
					indexblkno=pInode->indirBlockPtr;
					memset(pBuf,0,BLOCK_SIZE);
					DevReadBlock(indexblkno,pBuf);
					memcpy(indexblk,pBuf,BLOCK_SIZE);
					for(c=0;c<BLOCK_SIZE/sizeof(int);c++)
					{
						if(indexblk[c]!=0)
							if(blkno=indexblk[c])
								blkdelete(blkno);
					}
					blkdelete(indexblkno);
					pInode->indirBlockPtr=255;
					}
					pInode->dirBlockPtr[0]=255;


					PutInode(inodeno,pInode);
					//printf("%s 삭제완료 \n",path[k-1]);
					return 0;
				}
			}
		}
return -1;
}

int		MakeDir(const char* szDirName)
{

	char strstr[50];  char buf[60]; 	char * pch; int k;
	unsigned int * indexblk=(unsigned int *)calloc(BLOCK_SIZE,1);
	Inode *pInode=(Inode *)calloc(BLOCK_SIZE/4,1);
	DirEntry diren[NUM_OF_DIRENT_PER_BLOCK];
	memset(diren,0,BLOCK_SIZE);
	int Is=0;int prevInode =0;int prevblk=0;
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	char *path[12];
	for (int i = 0; i < 12; i++)
		path[i] = 0;
	strcpy(strstr, szDirName);
	//	printf("생성 중path :%s : ",strstr);
	k=0;
	pch = strtok(strstr, "/");
	while (pch != NULL)
	{
		path[k]=pch;
		pch = strtok(NULL, "/");
		k++;
	}//i는 경로들의 숫자 // path[i]로 하나씩 빼내면 됨 


	inodeno=0;
//	strcpy(prevInode,dir.inodeNum);
	for(int count=0;count<k-1;count++){
		for(int ptr=0;ptr<NUM_OF_DIRECT_BLOCK_PTR;ptr++)
		{	memset(pInode,255,sizeof(Inode));
			GetInode(inodeno,pInode);
			blkno=pInode->dirBlockPtr[ptr];
			DevReadBlock(blkno,pBuf);
			memcpy(diren, pBuf, BLOCK_SIZE);
			for (int i=0;i<4;i++)
			{
				if(!strcmp(diren[i].name,path[count]))
					{
						inodeno=diren[i].inodeNum;

						Is=1;
						break;
					}
			}
			if(Is)
			break;
		}

		if(!Is)
		{
			memset(pInode,255,sizeof(Inode));
			GetInode(inodeno,pInode);
			indexblkno=pInode->indirBlockPtr;
			DevReadBlock(blkno ,pBuf);
			memcpy(indexblk,pBuf,BLOCK_SIZE);//인다이렉트블록들을 배열로 하나하나 접속한다 단 i번째부터 쭉쭉
			for(int i=0;i<BLOCK_SIZE/sizeof(int);i++){
				blkno=indexblk[i];
				memset(pBuf,0,BLOCK_SIZE);
				DevReadBlock(blkno ,pBuf);
				memcpy(diren, pBuf, BLOCK_SIZE);
				if(!strcmp(diren[i].name,path[count]))
				{
					inodeno=diren[i].inodeNum;
					//printf("경로가 인다이렉트");
					break;
				}
			}
		}
		
	}//경로가 제대로 붙어있

	//printf("경로 노드 : %d,블럭 :%d ,k %d 최종경로 %s\n",inodeno,blkno,k,path[k-1]);

		for(int ptr=0;ptr<NUM_OF_DIRECT_BLOCK_PTR;ptr++){//두번째 확장까지만 허용 세번째는 따로 설정
				memset(pInode,255,sizeof(Inode));
				GetInode(inodeno,pInode);
				if(pInode->dirBlockPtr[ptr]==255)
				{
					blkno=GetFreeBlockNum();
					SetBlockBitmap(blkno);
					Plusblk();
					pInode->dirBlockPtr[ptr]=blkno;
				}
				blkno=pInode->dirBlockPtr[ptr];//여기서 처음 블럭 받아오고//다른데도 한번 훑어보
				DevReadBlock(blkno,pBuf);
				memcpy(diren, pBuf, BLOCK_SIZE);

				for (int i=0;i<4;i++)
				{
					if(!strcmp(diren[i].name,""))
					{
						PutInode(inodeno,pInode);
						prevInode=inodeno;//".."에 넣을값
						inodeno=GetFreeInodeNum();
						SetInodeBitmap(inodeno);
						memset(pBuf,0,BLOCK_SIZE);
						prevblk=blkno;
						strcpy(diren[i].name,path[k-1]);
						diren[i].inodeNum=inodeno;
						memcpy(pBuf, diren, BLOCK_SIZE);
						memset(diren,0,BLOCK_SIZE);
					//	printf("시작부터 ?%s\n",diren[0].name);

						DevWriteBlock(blkno ,pBuf);//inode에 비어있는 블록넘버의 블록 셋팅
						memset(pInode,255,sizeof(Inode));
						GetInode(inodeno,pInode);
						pInode->size=64;//아직 크기가 0
						pInode->type=1;//dir타입
						blkno=GetFreeBlockNum();
						SetBlockBitmap(blkno);
						Plusblk();
						//printf("블럭넘버 %d , %d 번 아이노드 0번째에 저장함!\n",blkno,inodeno);
						pInode->dirBlockPtr[0]=blkno;
						pInode->dirBlockPtr[1]=255;
						pInode->indirBlockPtr=255;// 폴더 만들때 1번 다이렉트랑 인다이렉트 -1 입력
						PutInode(inodeno,pInode);//한번뿐이잖
						PlusFile();
						strcpy(diren[0].name,".");
						diren[0].inodeNum=inodeno;
						strcpy(diren[1].name,"..");	
						diren[1].inodeNum=prevInode;
						memset(pBuf, 0, BLOCK_SIZE);
						memcpy(pBuf, diren, BLOCK_SIZE);
						memset(diren,0,BLOCK_SIZE);
						DevWriteBlock(blkno ,pBuf);//다시 가져올수있나 테스트

						return 0;
					}
				}
			}//이게 안되면 indirectblockd으로
			if(pInode->indirBlockPtr==255)
			{
				//만약 없으면 생성하기
				indexblkno=GetFreeBlockNum();

				SetBlockBitmap(indexblkno);//이 블록은 인다이렉트 인덱스 블록
				Plusblk();
				pInode->indirBlockPtr=indexblkno;
				PutInode(inodeno,pInode);

				memset(pBuf,0,BLOCK_SIZE);//인다이렉트 블럭으로 넘어가는 함수 설정해야됨 없으면 생성

				for(int i=0;i<BLOCK_SIZE;i++)//인덱스블록 초기화
					indexblk[i]=0;
				memcpy(pBuf,indexblk,BLOCK_SIZE);
				DevWriteBlock(indexblkno,pBuf);

				}
			else
				indexblkno=pInode->indirBlockPtr;

			DevReadBlock(indexblkno ,pBuf);
			memcpy(indexblk,pBuf,BLOCK_SIZE);
			for(int i=0;i<BLOCK_SIZE/sizeof(int);i++)
			{
				memset(pBuf,0,BLOCK_SIZE);
				if(indexblk[i]==0){
					blkno=GetFreeBlockNum();
					indexblk[i]=blkno;

					SetBlockBitmap(blkno);
					Plusblk();
					memcpy(pBuf, indexblk, BLOCK_SIZE);
					DevWriteBlock(indexblkno,pBuf);

				memset(indexblk,0,BLOCK_SIZE);
				DevReadBlock(indexblkno ,pBuf);
				memcpy(indexblk,pBuf,BLOCK_SIZE);

				}
				else{
				blkno=indexblk[i];

				}
					DevReadBlock(blkno ,pBuf);
					memcpy(diren, pBuf, BLOCK_SIZE);


				for (int l=0;l<4;l++)
				{
					//printf("비교 한것좀 보자 [%s ? ] ",diren[l].name);
					if(!strcmp(diren[l].name,""))
					{
						prevblk=blkno;
						prevInode=inodeno;//".."에 넣을값
						inodeno=GetFreeInodeNum();

						SetInodeBitmap(inodeno);
						memset(pBuf,0,BLOCK_SIZE);

						strcpy(diren[l].name,path[k-1]);
						diren[l].inodeNum=inodeno;
						memcpy(pBuf, diren, BLOCK_SIZE);
						DevWriteBlock(blkno ,pBuf);//inode에 비어있는 블록넘버의 블록 셋팅
						memset(diren,0,BLOCK_SIZE);
						memset(pInode,255,sizeof(Inode));
						GetInode(inodeno,pInode);
						pInode->size=64;//아직 크기가 0
						pInode->type=1;//dir타입
						blkno=GetFreeBlockNum();
						SetBlockBitmap(blkno);
						Plusblk();
						pInode->dirBlockPtr[0]=blkno;
						pInode->dirBlockPtr[1]=255;
						pInode->indirBlockPtr=255;// 폴더 만들때 1번 다이렉트랑 인다이렉트 -1 입력
						PutInode(inodeno,pInode);//한번뿐이잖
						PlusFile();
						strcpy(diren[0].name,".");
						diren[0].inodeNum=inodeno;
						strcpy(diren[1].name,"..");
						diren[1].inodeNum=prevInode;
						memset(pBuf, 0, BLOCK_SIZE);
						memcpy(pBuf, diren, BLOCK_SIZE);
						memset(diren,0,BLOCK_SIZE);
						DevWriteBlock(blkno ,pBuf);//다시 가져올수있나 테스트
						/*
						memset(pBuf, 0, BLOCK_SIZE);
						DevReadBlock(prevblk ,pBuf);
						memset(diren,0,BLOCK_SIZE);
						memcpy(diren,pBuf, BLOCK_SIZE);*/


//printf("%s폴더 생성 성공 ,inode :%d , blk : %d ,dir:indirect[%d], indexblk[%d]\n",path[k-1],inodeno,blkno,indexblkno,indexblk[i]);

						return 0;
					}

				}

		}
}
void PlusFile(){
	unsigned char *pBuf = (unsigned char *)calloc(BLOCK_SIZE, 1);

		FileSysInfo  *fn=calloc(BLOCK_SIZE,1);
		DevReadBlock(FILESYS_INFO_BLOCK ,(char *)fn);//파일시스템 정보 불러오기
		fn->numAllocInodes++;
		// 다시불러올때 fn = (FileSysInfo *)pBuf;	
		DevWriteBlock(FILESYS_INFO_BLOCK,(char *)fn);

}

void MinusFile(){
		FileSysInfo  *fn=calloc(BLOCK_SIZE,1);
		memset(fn,0,BLOCK_SIZE);
		DevReadBlock(FILESYS_INFO_BLOCK,(char *)fn);
		fn->numAllocInodes--;
		DevWriteBlock(FILESYS_INFO_BLOCK,(char *)fn);
}
void Plusblk(){
		FileSysInfo  *fn=calloc(BLOCK_SIZE,1);
		memset(fn,0,BLOCK_SIZE);
		DevReadBlock(FILESYS_INFO_BLOCK,(char *)fn);
		fn->numAllocBlocks++;
		fn->numFreeBlocks--;
		DevWriteBlock(FILESYS_INFO_BLOCK,(char *)fn);
}
void Minusblk(){
		FileSysInfo  *fn=calloc(BLOCK_SIZE,1);
			memset(fn,0,BLOCK_SIZE);
			DevReadBlock(FILESYS_INFO_BLOCK,(char *)fn);
			fn->numAllocBlocks--;
			fn->numFreeBlocks++;
			DevWriteBlock(FILESYS_INFO_BLOCK,(char *)fn);
}


int		RemoveDir(const char* szDirName)
{
	unsigned int * indexblk=(unsigned int *)calloc(BLOCK_SIZE,1);
	char strstr[50];  char buf[60]; 	char * pch; int k=0;int noempty=0;;
	 int c;int prev_blk;int prev_inodeno;
	Inode *pInode=(Inode *)calloc(BLOCK_SIZE/4,1);

	DirEntry diren[NUM_OF_DIRENT_PER_BLOCK]; int Is=0;int prevInode =0;
	unsigned char *pBuf=(unsigned char *)calloc(1,BLOCK_SIZE);
	char *path[12];
	for (int i = 0; i < 12; i++)
		path[i] = 0;

	strcpy(strstr, szDirName);
	k=0;
	pch = strtok(strstr, "/");
	while (pch != NULL)
	{
		path[k]=pch;
		pch = strtok(NULL, "/");
		k++;
	}//i는 경로들의 갯수 // path[i]로 하나씩 빼서쓰면

	//printf(" '%s' 삭제접수\n",path[k-1]);
	inodeno=0;
//	strcpy(prevInode,dir.inodeNum);
	for(int count=0;count<k-1;count++){
//printf(" %s path[count] 찾는중\n",path[count]);
		for(int ptr=0;ptr<NUM_OF_DIRECT_BLOCK_PTR;ptr++)
		{


			for (int i=0;i<4;i++)
			{
				memset(pInode,0,sizeof(Inode));
				GetInode(inodeno,pInode);
				blkno=pInode->dirBlockPtr[ptr];
				memset(pBuf,0,BLOCK_SIZE);
				DevReadBlock(blkno,pBuf);
				memcpy(diren, pBuf, BLOCK_SIZE);
				if(!strcmp(diren[i].name,path[count]))
					{
						inodeno=diren[i].inodeNum;
						Is=1;
						break;
					}
			}
			if(Is)
				break;
		}

		if(!Is)
		{
			memset(pInode,0,sizeof(Inode));
			GetInode(inodeno,pInode);
			indexblkno=pInode->indirBlockPtr;
			memset(pBuf,0,BLOCK_SIZE);
			DevReadBlock(blkno ,pBuf);
			memcpy(indexblk,pBuf,BLOCK_SIZE);//인다이렉트블록들을 배열로 하나하나 접속한다 단 i번째부터 쭉쭉
			for(int i=0;i<BLOCK_SIZE/sizeof(int);i++){
				blkno=indexblk[i];
				memset(pBuf,0,BLOCK_SIZE);
				DevReadBlock(blkno ,pBuf);
				memcpy(diren, pBuf, BLOCK_SIZE);
				if(!strcmp(diren[i].name,path[count]))
				{
					inodeno=diren[i].inodeNum;
					//printf("여기는?");
					break;

				}
			}
		}

	}//COUNT FOR문 종료
	//그럼 inodeg획득했으니 그에 해당하는 block속 =파일생성하기
		for(int ptr=0;ptr<NUM_OF_DIRECT_BLOCK_PTR;ptr++){
				memset(diren,0,BLOCK_SIZE);
				memset(pInode,0,sizeof(Inode));
				GetInode(inodeno,pInode);
				blkno=pInode->dirBlockPtr[ptr];
				DevReadBlock(blkno,pBuf);
				memcpy(diren, pBuf, BLOCK_SIZE);

				for (int i=0;i<4;i++)
				{
		//	printf("다이렉트 블럭안 [%s] 삭제대상  찾는중 [%s]랑 비교\n",path[k-1],diren[i].name);
			//printf("여기 무엇이 오느냐 %s \n",diren[i].name);
					if(!strcmp(diren[i].name,path[k-1]))
						{

						prev_inodeno=inodeno;
						inodeno=diren[i].inodeNum;
						memset(pInode,0,sizeof(Inode));
						GetInode(inodeno,pInode);
						//printf("[1]%d, indire_b_p [%d]",pInode->dirBlockPtr[1], pInode->indirBlockPtr);

					if((pInode->dirBlockPtr[1]==255)&&(pInode->indirBlockPtr==255))
						{
							diren[i].inodeNum=255;
							strcpy(diren[i].name,"");
							memcpy(pBuf, diren, BLOCK_SIZE);;
							DevWriteBlock(blkno,pBuf);

							prev_blk=blkno;
							memset(pBuf, 0, BLOCK_SIZE);
							blkno=pInode->dirBlockPtr[0];
							DevReadBlock(blkno,pBuf);
							memcpy(diren, pBuf, BLOCK_SIZE);
							for(c=2;c<4;c++)
							{
								if(strcmp(diren[c].name,""))
								return -1;
							}

							ResetBlockBitmap(blkno);
							Minusblk();
							pInode->dirBlockPtr[0]=255;
							PutInode(inodeno,pInode);
							ResetInodeBitmap(inodeno);
						//printInodeBitmap();
							MinusFile();
							for(int k=0;k<2;k++){
								strcpy(diren[k].name,"");
								diren[k].inodeNum=255;}

							memcpy(pBuf, diren, BLOCK_SIZE);
							DevWriteBlock(blkno ,pBuf);//깔끔 끝0으로 초기화
							memset(pBuf, 0, BLOCK_SIZE);

						//	printf("!!지움 ");printf("%s\n",path[k-1]);

		//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ 아무것도 없다면 해당 블럭 삭제
		//현재 아이노드가 주어져있는상태 ptr은 그냥쓰는데로
							noempty=0;
							memset(pInode,0,sizeof(Inode));
							GetInode(prev_inodeno,pInode);
							blkno=pInode->dirBlockPtr[ptr];
							memset(pBuf, 0, BLOCK_SIZE);
							DevReadBlock(blkno,pBuf);
							memset(diren,0,BLOCK_SIZE);
							memcpy(diren, pBuf, BLOCK_SIZE);
			//여기까지했음
							noempty=0;
							for (int i=0;i<4;i++)
							{

							if(!(!strcmp(diren[i].name,"")|!strcmp(diren[i].name,"..")))
								{

									noempty=1;
								}
							}
							if(!noempty)
							{
								ResetBlockBitmap(blkno);
								Minusblk();
								ResetInodeBitmap(inodeno);
								pInode->dirBlockPtr[ptr]=255;
								PutInode(prev_inodeno,pInode);
								ResetInodeBitmap(inodeno);
							}
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
					//	printf("삭제완료");printf("%s\n",path[k-1]);
					return 0;
						}
						else
						return -1;
					}
				}
			}
	if(pInode->indirBlockPtr!=255){
		indexblkno=pInode->indirBlockPtr;
		memset(pBuf,0,BLOCK_SIZE);
		DevReadBlock(indexblkno ,pBuf);
		memcpy(indexblk,pBuf,BLOCK_SIZE);
		memset(diren,0,BLOCK_SIZE);
		for(int l=0;l<BLOCK_SIZE/sizeof(int);l++)
		{
			memset(pBuf,0,BLOCK_SIZE);
			blkno=indexblk[l];
			DevReadBlock(blkno ,pBuf);
			memcpy(diren, pBuf, BLOCK_SIZE);
			
			for (int i=0;i<4;i++)
			{
				//printf("인다이렉트 블럭안 [%s] 삭제대상  찾는중 [%s]랑 비교\n",path[k-1],diren[i].name);
				if(!strcmp(diren[i].name,path[k-1]))
				{
					prev_inodeno=inodeno;
					inodeno=diren[i].inodeNum;
					memset(pInode,0,sizeof(Inode));
					GetInode(inodeno,pInode);

					if((pInode->dirBlockPtr[1]==255)&&(pInode->indirBlockPtr==255))
					{
						diren[i].inodeNum=255;
						strcpy(diren[i].name,"");
						memcpy(pBuf, diren, BLOCK_SIZE);;
						DevWriteBlock(blkno,pBuf);

						prev_blk=blkno;
						memset(pBuf, 0, BLOCK_SIZE);
						blkno=pInode->dirBlockPtr[0];
						DevReadBlock(blkno,pBuf);
						memcpy(diren, pBuf, BLOCK_SIZE);
						for(c=2;c<4;c++)
						{
						if(strcmp(diren[c].name,""))
						return -1;
						}
						ResetBlockBitmap(blkno);
						Minusblk();
						pInode->dirBlockPtr[0]=255;
						PutInode(inodeno,pInode);
						ResetInodeBitmap(inodeno);
						MinusFile();
						for(int k=0;k<2;k++){
							strcpy(diren[k].name,"");
							diren[k].inodeNum=255;}
						memset(pBuf, 0, BLOCK_SIZE);
						memcpy(pBuf, diren, BLOCK_SIZE);//초기화 다시켜놧는데?
						DevWriteBlock(blkno ,pBuf);
						//printf("번호!! %d\n",blkno);
			//printf("삭제완료");printf("%s\n",path[k-1]);
					//	printInodeBitmap();
					//	printf("지움 ");printf("%s\n",path[k-1]);
//비어있으면 삭제 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

						memset(pInode,0,sizeof(Inode));
						//GetInode(prev_inodeno,pInode);
						blkno=indexblk[l];
						memset(pBuf, 0, BLOCK_SIZE);
						DevReadBlock(blkno,pBuf);

						memset(diren,0,BLOCK_SIZE);
						memcpy(diren, pBuf, BLOCK_SIZE);
		//여기까지했음
						noempty=0;
						for (int i=0;i<4;i++)
						{
//printf(" blk [%d,%d] 삭제하러 오냐? : %s\n ",blkno,indexblk[l],diren[i].name);
						//printf("리스트 %s \n",diren[i].name);
						if(!(!strcmp(diren[i].name,"")|!strcmp(diren[i].name,"..")))
							{
								noempty=1;

							}

						}
						if(!noempty)
						{

				//printf("삭제하러 오냐?");
							ResetBlockBitmap(blkno);
							Minusblk();
							indexblk[l]=0;
							memcpy(pBuf,indexblk,BLOCK_SIZE);
							DevWriteBlock(indexblkno ,pBuf);


						}
						//상위 인덱스 블럭안이 다비었는가 체크후 다비었으면 삭제
						noempty=0;
						for(int l=0;l<BLOCK_SIZE/sizeof(int);l++)
							if(indexblk[l]!=0){
								//printf("indexblk[%d] ?: %d\n",l,indexblk[l]);
								noempty=1;}
	if(!strcmp(path[k-1],"dev6"))
//printf("누가왓을까 %s %d\n",path[k-1],noempty );
						if(!noempty)
						{
							memset(pInode,0,sizeof(Inode));
							GetInode(prev_inodeno,pInode);
							blkno=pInode->indirBlockPtr;
							ResetBlockBitmap(blkno);
							Minusblk();
				//printf("아이노드값은? %d",prev_inodeno);
							pInode->indirBlockPtr=255;
							PutInode(prev_inodeno,pInode);
						}
							return 0;//위랑 똑같이 상위노드에서

					}
					else
					return -1;
				}
			}//for=4문 임
		}
	}
return -1;
}


extern int 		EnumerateDirStatus(const char* szDirName, DirEntryInfo* pDirEntry, int dirEntrys )
{//(const char* szDirName, DirEntry* pDirEntry, int* pNum)
	
//printBlkBitmap();
//printInodeBitmap();

//printf("last state bitsetblkcount : %d\n",setblk);
//printf("last state bitresetblkcount : %d\n",resetblk);
	char strstr[50]; char buf[60]; 	char * pch; int entryno;int k;
	unsigned int * indexblk=(unsigned int *)calloc(BLOCK_SIZE,1);
	Inode *pInode=(Inode *)calloc(BLOCK_SIZE/4,1);
	DirEntry diren[NUM_OF_DIRENT_PER_BLOCK];int Is=0;int prevInode =0;
	DirEntryInfo Temp_Entry={0,};
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);

	entryno=0;
//printf("비트맵 셋팅 : \n");
//printInodeBitmap();
	char *path[12];
	for (int i = 0; i < 12; i++)
		path[i] = 0;
	strcpy(strstr, szDirName);
//	printf("'인쇄할 경로 %s' ",strstr);
//	printf("%s",strstr);
	k=0;
	pch = strtok(strstr, "/");
	while (pch != NULL)
	{
		path[k]=pch;
		pch = strtok(NULL, "/");
		k++;
	}//i는 경로들의 갯수 // path[i]로 하나씩 빼서쓰면


	inodeno=0;
//	strcpy(prevInode,dir.inodeNum);
	for(int count=0;count<k;count++){Is=0;
		for(int ptr=0;ptr<NUM_OF_DIRECT_BLOCK_PTR;ptr++)
			{
			memset(pInode,255,sizeof(Inode));
			GetInode(inodeno,pInode);
			blkno=pInode->dirBlockPtr[ptr];
			memset(pBuf,0,BLOCK_SIZE);
			memset(diren, 0, BLOCK_SIZE);
			DevReadBlock(blkno,pBuf);
			memcpy(diren, pBuf, BLOCK_SIZE);
		for (int i=0;i<4;i++)
			{
		//		printf("출력전 이름 출력 [%s ? %s ] 블럭 %d \n",diren[i].name,path[count],blkno);
				if(!strcmp(diren[i].name,path[count]))
					{
						inodeno=diren[i].inodeNum;
						Is=1;
						break;
					}
			}
			if(Is)
			break;
		}

		if(!Is)
		{
			memset(pInode,255,sizeof(Inode));
			GetInode(inodeno,pInode);
			indexblkno=pInode->indirBlockPtr;
			//printf("인다이렉트 블럭? %d\n",indexblkno);
			DevReadBlock(indexblkno ,pBuf);
			memcpy(indexblk,pBuf,BLOCK_SIZE);//인다이렉트블록들을 배열로 하나하나 접속한다 단 i번째부터 쭉쭉
			for(int i=0;i<BLOCK_SIZE/sizeof(int);i++){
				blkno=indexblk[i];
				memset(pBuf,0,BLOCK_SIZE);
				DevReadBlock(blkno ,pBuf);
				memcpy(diren, pBuf, BLOCK_SIZE);
				//printf("indirect 출력전 이름 출력 [%s ? %s ] 블럭 %d \n",diren[i].name,path[count],blkno);
				if(!strcmp(diren[i].name,path[count]))
				{
					inodeno=diren[i].inodeNum;
				//	printf("여기는?");
					break;

				}
			}
		}

	}
		//해당파일의 inode를 얻어왓음
//printf("아이노드 넘버 : %d",inodeno);

//		printf("path [%s] blkno : [%d]\n",path[k-1],blkno);
		for(int ptr=0;ptr<NUM_OF_DIRECT_BLOCK_PTR;ptr++){
				memset(pInode,0,sizeof(Inode));
				GetInode(inodeno,pInode);
				blkno=pInode->dirBlockPtr[ptr];

				DevReadBlock(blkno,pBuf);
				memset(diren,0,BLOCK_SIZE);
				memcpy(diren, pBuf, BLOCK_SIZE);
//여기까지했음
				for (int i=0;i<4;i++)
				{

					if(strcmp(diren[i].name,""))
					{

						if(dirEntrys>entryno){

						//	printf(" %d : 번째 ",entryno +1);
							strcpy(Temp_Entry.name ,diren[i].name);
							Temp_Entry.inodeNum=diren[i].inodeNum;
//printf("다이렉트 이름 %s 아이노드 %d \n",diren[i].name,diren[i].inodeNum);
							memset(pInode,0,sizeof(Inode));
							GetInode(diren[i].inodeNum,pInode);
							pInode->size=0;//아직 크기가 0파일이기때문에
							Temp_Entry.type=pInode->type;//dir타입//??????????????????!!!!!!!!!!!!!!!!!!????
							pDirEntry[entryno]=Temp_Entry;

							entryno++;
						}
						else
							return entryno;
					}
				}

		}
		memset(pInode,0,sizeof(Inode));
		GetInode(inodeno,pInode);
		indexblkno=pInode->indirBlockPtr;
		if(indexblkno!=0)
		{
			memset(indexblk,0,BLOCK_SIZE);
			DevReadBlock(indexblkno ,pBuf);
			memcpy(indexblk,pBuf,BLOCK_SIZE);
		}
	for(int i=0;i<BLOCK_SIZE/sizeof(int);i++)
	{


		if(indexblk[i]!=0)
		{
			blkno=indexblk[i];

			DevReadBlock(blkno ,pBuf);//불러왔을땐 깨끗한상태
			memcpy(diren, pBuf, BLOCK_SIZE);

			for (int l=0;l<4;l++)
			{
				if(strcmp(diren[l].name,""))
				{

					if(dirEntrys>entryno){
						memcpy(Temp_Entry.name ,diren[l].name,MAX_NAME_LEN);
						Temp_Entry.inodeNum=diren[l].inodeNum;
						memset(pInode,0,sizeof(Inode));
//printf("인다이렉트 이름 %s 아이노드 %d \n",diren[l].name,diren[l].inodeNum);
						GetInode(diren[l].inodeNum,pInode);
						pInode->size=0;//아직 크기가 0파일이기때문에
						Temp_Entry.type=pInode->type;//dir타입//??????????????????!!!!!!!!!!!!!!!!!!????
						pDirEntry[entryno]=Temp_Entry;
						entryno++;
					}
					else
						return entryno;
				}
				else
					return entryno;
			}
		}
	}

//printf("entry 갯수%d",entryno);
	return entryno;
}

void blkdelete(int blk)
{
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	memset(pBuf, 0, BLOCK_SIZE);
	ResetBlockBitmap(blk);
	DevWriteBlock(blk,pBuf);
	Minusblk();
}


