#include<iostream>
#include<stdlib.h>
using namespace std;

int counter = 0;
/***************** Parameter Setting *****************/
int const InsideCount = 3;//frames
int Inside[InsideCount];
int const PageCount = 20;//总的页面数
int Page[PageCount] = {1,2,3,4,2,1,5,6,2,1,2,3,7,6,3,2,1,2,3,6};

int insert = 0;//used in FIFO algorithm
double lost = 0.0;//used to count the number of page faults

bool isInside(int num)//check whether the page is in memory or not
{
    //added code
    bool res=false;
    for(int i = 0; i < InsideCount; i++)
    {
        if(Inside[i] == Page[num])
        {
            res=true;
        }
    }
    return res;
    //***********
}

void LRU(int num)
{
    int max = 0;   //记录页面下一次或上一次出现到这次出现的距离
    int maxchange; //表示出现距离最大的页号在内存中的位置
    int k;
    if(isInside(num))
    {
        cout<<"It is already in memory!"<<endl;
        for(int i=0 ; i <InsideCount; i++)
            cout<<"Inside["<<i<<"]:"<<Inside [i]<<endl;
    }
    else
        if(counter == InsideCount)//if the frames are full
        {
            lost++;
            for(int j=0; j < InsideCount; j++)
            {
                //从当前的页号向该页的前面(左)看，找到距离最远的页面，并记录下距离最远的页面所在内存物理帧位置
                //added code
                for(k = num;k>0;k--)
                {
                    if(Inside[j] == Page[k])
                        break;
                }
                if(num - k > max)
                {
                    max = num - k;
                    maxchange =j;
                }
                //***********
            }
            //进行页面置换
            //added code
            Inside[maxchange] = Page[num];
            //***********
            
            for(int i=0 ; i <InsideCount; i++)
                cout<<"Inside["<<i<<"]:"<<Inside [i]<<endl;
        }
        else//there are free frames in memory
        {
            //if there are free frames in memory, the pages can be loaded into frames directly.
            //added code
            Inside[counter] = Page[num];
            counter++;
            //***********
            
            for(int i=0 ; i <InsideCount; i++)
                cout<<"Inside["<<i<<"]:"<<Inside [i]<<endl;
        }
}

void FIFO(int num)
{
    if(isInside(num))
    {
        cout<<"It is already in memory!"<<endl;
        for(int i=0 ; i <InsideCount; i++)
            cout<<"Inside["<<i<<"]:"<<Inside [i]<<endl;
    }
    else
        if(counter == InsideCount)//if the frames are full
        {
            lost++;
            //use the “insert” to record the position of current page in memory, the "insert" should be changed after page replacement
            //added code
            Inside[insert] = Page[num];
            insert++;
            insert = insert % 3;
            //***********
            
            for(int i=0 ; i <InsideCount; i++)
                cout<<"Inside["<<i<<"]:"<<Inside [i]<<endl;
        }
        else
        {
            //if there are free frames in memory, the pages can be loaded into frames directly.
            //added code
            Inside[counter] = Page[num];
            counter++;
            //***********
            
            for(int i=0 ; i <InsideCount; i++)
                cout<<"Inside["<<i<<"]:"<<Inside [i]<<endl;
        }
}

void MIN(int num)
{
    int max = 0;
    int maxchange;
    int k;
    if(isInside(num))
    {
        cout<<"It is already in memory!"<<endl;
        for(int i=0 ; i <InsideCount; i++)
            cout<<"Inside["<<i<<"]:"<<Inside [i]<<endl;
    }
    else
        if(counter == InsideCount)//if the frames are full
        {
            lost++;
            for(int j=0; j < InsideCount; j++)
            {
                //从当前的页号向该页的后面(右)看，找到距离最远的页号后，记录此时内存物理帧位置
                //added code
                for( k = num; k < PageCount;k++)
                {
                    if(Inside[j] == Page[k])
                        break;
                }
                if( k > max)
                {
                    max = k;    //k表示在这个地方会再次出现给定页面
                    maxchange =j;//j 表示把 内存中第j个Inside中的页面从内存拿出，把新的页面放入
                }
                //***********
                
            }
            //进行页面置换
            //added code
            Inside[maxchange] = Page[num];
            //***********
            
            for(int i=0 ; i <InsideCount; i++)
                cout<<"Inside["<<i<<"]:"<<Inside [i]<<endl;
        }
        else
        {
            //if there are free frames in memory, the pages can be loaded into frames directly.
            //added code
            Inside[counter] = Page[num];
            counter++;
            //***********
            
            for(int i=0 ; i <InsideCount; i++)
                cout<<"Inside["<<i<<"]:"<<Inside [i]<<endl;
        }
}

int main()
{
    char ch ;
    while(1)
    {
        cout<<"M: MIN"<<"\n"<<endl;
        cout<<"F: FIFO"<<"\n"<<endl;
        cout<<"L: LRU"<<"\n"<<endl;
        cin>>ch;
        switch(ch)
        {
            case 'M':
            {
                lost = 0;
                counter = 0;
                for(int j = 0; j < InsideCount; j++)
                {
                    Inside[j] = 0;
                }
                for(int i = 0; i < PageCount; i++)
                {
                    cout<<"Accessing Page["<<i<<"]="<<Page[i]<<endl;
                    MIN(i);
                }
                cout<<"Accessing " <<PageCount<<" pages, "<<"page faults "<<lost<<" times, page-fault rate is "<<lost/(PageCount)<<"\n\n"<<endl;
            }
                break;
            case 'F':
            {
                lost =  0;
                counter = 0;
                for(int j = 0; j < InsideCount; j++)
                {
                    Inside[j] = 0;
                }
                for(int i = 0; i < PageCount; i++)
                {
                    cout<<"Accessing Page["<<i<<"]="<<Page[i]<<endl;
                    FIFO(i);
                }
                cout<<"Accessing " <<PageCount<<" pages, "<<"page faults "<<lost<<" times, page-fault rate is "<<lost/(PageCount)<<"\n\n"<<endl;
            }
                break;
            case 'L':
            {
                lost = 0;
                counter = 0;
                for(int j = 0; j < InsideCount; j++)
                {
                    Inside[j] = 0;
                }
                for(int i = 0; i < PageCount; i++)
                {
                    cout<<"Accessing Page["<<i<<"]="<<Page[i]<<endl;
                    LRU(i);
                }
                cout<<"Accessing " <<PageCount<<" pages, "<<"page faults "<<lost<<" times, page-fault rate is "<<lost/(PageCount)<<"\n\n"<<endl;
            }
                break;
        }
    }
    return 0;
}

