#include <stdio.h>
#include<stdlib.h>
#include "fs.h"
#include "disk.h"
#include<string.h>

char *bi(unsigned long n)
{
static char s[BLOCK_SIZE+1]={0};
char *p=s+BLOCK_SIZE;
while(n){
	p--;
	*p=(n&1)?'1':'0';
	n>>=1;
	}
	return p;
}

void FileSysInit(void)
{
	DevCreateDisk();// create disk
	DevOpenDisk();
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	//char *pBuf=(char*)malloc(BLOCK_SIZE*sizeof(char));
	//memset(pBuf,0,BLOCK_SIZE);
	int i;
	for(i=0;i<=6;i++)
		DevWriteBlock(i,pBuf);
	/*	printf("seting value\n,");
	for(i=0;i<=512;i++)
		printf("%d,",pBuf[i]);
		printf("end\n,"); */
	
	free(pBuf);
}
void SetInodeBitmap(int inodeno)
{	
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	DevReadBlock(INODE_BITMAP_BLK_NUM ,pBuf);
	pBuf[(int)(inodeno/8)]|=(1<<7-(inodeno%8));//i think so
	DevWriteBlock(INODE_BITMAP_BLK_NUM ,pBuf);

	free(pBuf);
}


void ResetInodeBitmap(int inodeno)
{
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	DevReadBlock(INODE_BITMAP_BLK_NUM ,pBuf);
	pBuf[(int)(inodeno/8)]&=~(1<<7-(inodeno%8));//!->~ change
	DevWriteBlock(INODE_BITMAP_BLK_NUM ,pBuf);
	free(pBuf);
}


void SetBlockBitmap(int blkno)
{	//printf("\nblkno:%d\n byteno:%d\n",blkno,(int)(blkno/8));//test
	//printf("\n(%s)\n",bi(blkno));//test
	
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
//	printf("to set block num: %d\n",blkno);
	DevReadBlock(BLOCK_BITMAP_BLK_NUM ,pBuf);
//	printf("pBuf value [%d] after load: %d\n",(blkno/8),pBuf[(blkno/8)]);
	pBuf[(int)(blkno/8)]|=(1<<(7-(blkno%8)));
	DevWriteBlock(BLOCK_BITMAP_BLK_NUM ,pBuf);
//	printf("PBuf[%d] value after write:%d\n",(int)(blkno/8),pBuf[(int)(blkno/8)]);

	
/*	printf("value after seting\n,");
	for(int i=0;i<=512;i++)
		printf("%d,",pBuf[i]);
		printf("end\n,");
*/

	free(pBuf);
}


void ResetBlockBitmap(int blkno)
{
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	DevReadBlock(BLOCK_BITMAP_BLK_NUM ,pBuf);
	pBuf[(int)(blkno/8)]&=~(1<<7-(blkno%8));
	DevWriteBlock(BLOCK_BITMAP_BLK_NUM ,pBuf);
	free(pBuf);
}


void PutInode(int inodeno, Inode* pInode)
{
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	int inodeindex=0;
	inodeindex=((inodeno%8)*64);

	pBuf[inodeindex]=pInode->allocBlocks;
	pBuf[inodeindex+4]=pInode->type;
	for(int i=2;i<=16;i++)
		pBuf[inodeindex+i*4]=pInode->blockPointer[i-2];
	DevWriteBlock((int)(inodeno/8)+3,pBuf);
	free(pBuf);

}

void GetInode(int inodeno, Inode* pInode)
{
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	DevReadBlock((int)(inodeno/8)+3,pBuf);
	int inodeindex=0;
	inodeindex=((inodeno%8)*64);

	pInode->allocBlocks = pBuf[inodeindex];
	pInode->type = pBuf[inodeindex+4];
	for(int i=2;i<=16;i++)
	        pInode->blockPointer[i-2]=pBuf[inodeindex+i*4];

	free(pBuf);	
}


int GetFreeInodeNum(void)
{
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	DevReadBlock(INODE_BITMAP_BLK_NUM ,pBuf);
	for(int l=0;l<64;l++){
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


int GetFreeBlockNum(void)
{
	unsigned char *pBuf=(unsigned char *)calloc(BLOCK_SIZE,1);
	DevReadBlock(BLOCK_BITMAP_BLK_NUM ,pBuf);
	for(int l=0;l<64;l++){
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






