#include<iostream>
#include<cstdlib>
#include<bits/stdc++.h>
#include<windows.h> 
using namespace std;

#define LBR '\n'

void go_back_n(int window_size,int num_frames)
{
    window_size =pow(2,window_size)-1;
    cout<<"Window size: "<<window_size<<LBR;
	int tr(0);
	srand(100);
     
	int i=1;

	while(i<=num_frames)
	{
		int inc=0;

		for(int j=i;j<i+window_size && j<=num_frames;j++)
		{
			cout<<"Sent frame "<<j<<LBR;
			tr++;
            Sleep(1000);
		}

		for(int j=i;j<i+window_size && j<=num_frames;j++)
		{
			int flag = rand()%2;

			if(!flag)
			{
				cout<<"Ack. received for "<<j<<LBR;
				tr++;
				inc++;
                Sleep(1000);
			}
			else{
				cout<<"Ack failed for "<<j<<LBR;
                Sleep(1000);
				cout<<"Restransmitting the window"<<LBR;
                Sleep(1000);
				break;
			}
		}
		i = i +inc;
		cout<<LBR;
        cout<<"<---Window slided--->"<<LBR;
		cout<<LBR;

	}
}

void selective_repeat(int window_size, int num_frames)
{
     window_size =pow(2,window_size-1);
    cout<<"Window size: "<<window_size<<LBR;
		int MAX_INPUT=1000;
	srand(100);
	
	int drop_pack[num_frames+1];
	int ack_rec =0;
	int last_pack =0;
	int last_pack_ack = last_pack;
	int insertHere = 1;
	int i=1;

	for(int i=0;i<=num_frames+1;i++)
	{
		drop_pack[i]=MAX_INPUT;
	}

	while(ack_rec < num_frames)
	{

		for (int i = 1; i <= window_size && ack_rec < num_frames; i++) {
    if (drop_pack[i] != MAX_INPUT) {
        // Frame has not been acknowledged, so it can be retransmitted.
        cout << "Sent frame " << drop_pack[i] << LBR;
        Sleep(1000);
    } else {
        // All frames within the window have been acknowledged, so don't send new frames.
        if (last_pack == num_frames) {
            continue;
        }
        cout << "Sent frame " << last_pack + 1 << LBR;
        last_pack++;
        insertHere++;
        Sleep(1000);
    }
}



		for(int i=1;i<=window_size && ack_rec<num_frames;i++)
		{
			int flag = rand()%2;
			if(!flag)
			{
				if(drop_pack[i]!=MAX_INPUT)
			{
				cout<<"Ack received for frame "<<drop_pack[i]<<LBR;
                Sleep(1000);
				drop_pack[i]=MAX_INPUT;
			}
			else{
				if(last_pack_ack==num_frames)
					continue;
				cout<<"Ack received for frame "<<last_pack_ack+1<<LBR;
                Sleep(1000);
				last_pack_ack++;
			}
			ack_rec++;
			cout<<LBR;
			cout<<"<---Window slides--->"<<LBR;
			cout<<LBR;
			}
			else{
				if(drop_pack[i]!=MAX_INPUT)
			{
				cout<<"Ack failed for frame "<<drop_pack[i]<<LBR;
                Sleep(1000);
			}
			else{
				if(last_pack_ack==num_frames)
					continue;
				cout<<"Ack failed for frame "<<last_pack_ack+1<<LBR;
                Sleep(1000);
				drop_pack[insertHere]=last_pack_ack+1;
				last_pack_ack++;
				insertHere++;
			}
			}
		}

		sort(drop_pack+1,drop_pack+num_frames+1);
		for(int i=1;i<=num_frames+1;i++)
		{
			if(drop_pack[i]==MAX_INPUT)
			{
				insertHere=i;
				break;
			}
		}

	}
}

int main()
{
	int choice;
    int nf,ws;
	cout << "Sliding Window Protocols" << LBR;
    cout<<"Enter the no of frames :";
	cin>>nf;
	cout<<"Enter the no of bits :";
	cin>>ws;
	
	while(1)
	{
		cout<<"\n1.Go-Back-N\n2.Selective Repeat\n3.Exit"<<LBR;
		cin>>choice;
		if(choice==1)
		{
			go_back_n(ws,nf);
		}
		else if(choice==2)
		{
			selective_repeat(ws,nf);
		}
		else if(choice==3)
		{
			exit(0);
		}
	}
}
