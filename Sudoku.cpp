/*
Sudoku Solver and Checker
By - Saksham Koul
*/
#include <bits/stdc++.h>
#include<windows.h>
#include<set>
using namespace std;

bool error = 0;
int c = 1;

void showString(char *s)
{
	for(int x = 0; x < strlen(s); x++)
	{
		cout<<s[x];
		Sleep(30);	
	}
	cout<<"\n";
}

class Sudoku
{
	int input[9][9];
    int sudoku[9][9];

	public:
        
        void showInput()
		{
			cout<<setw(85)<<"-------------------------\n"<<setw(61);
			for (int i = 0; i < 9; i++)
			{
				cout<<"| ";
				for (int j = 0; j < 9; j++)
				{
					if (j == 2 || j == 5)
					{
						if (input[i][j] == 0)
							cout<<'.'<<" | ";
						else
							cout<<input[i][j]<<" | ";	
					}
					else
					{
						if (input[i][j] == 0)
							cout<<'.'<<" ";
						else
							cout<<input[i][j]<<" ";		
					}
					
				}
				if (i == 2 || i == 5)
					cout<<"|\n"<<setw(85)<<"|-----------------------|\n"<<setw(61);
				else
					cout<<"|\n"<<setw(61);
			}
			cout<<setw(85)<<"-------------------------\n";
		}
        
        void takeinput()
		{
			error = 0;
            int i,j,k,c = 0;
            for(i = 0; i < 9; i++)
			{
                for(j = 0; j < 9; j++)		// taking input rowise
				{
                    cin>>input[i][j];
                    
                    if (input[i][j] < 0 || input[i][j] > 9)
                    {
                    	error = 1;
                    	return;
					}
                    sudoku[i][j] = input[i][j];
                }
            }
            
			//TESTS FOR INVALID INPUT
            
            //TEST 1 - Duplicate entries in row/col
         	for (i = 0; i < 8; i++)
			{
				for (j = 0; j < 8; j++)
				{
					int x = input[i][j];
					if (x == 0)
						continue;
					
					for (k = j+1; k < 9; k++)			//checking duplicate in row
					{
						if (input[i][k] == x)
						{
							cout<<"\nDuplicate entry in row "<<i+1<<endl;
							error = 1;
							return;
						}
					}
					
					for (k = i+1; k < 9; k++)			//checking duplicate in col
					{
						if (input[k][j] == x)
						{
							cout<<"\nDuplicate entry in column "<<j+1<<endl;
							error = 1;
							return;
						}
					}
				}
			}
			//TEST 2 - checking duplicates in box
			
			for(int row = 0; row < 9; row = row + 3)
			{
   				for(int col = 0; col < 9; col = col + 3)
				{
       				set<int> s;
       				for(int r = row; r < row + 3; r++)
					{
						for(int c = col; c < col + 3; c++)
						{
           					if(input[r][c] != 0)
		  					{
               					if(s.insert(input[r][c]).second == false)
								{
               						cout<<"\nDuplicate entry in sub-square"<<endl;
               						error = 1;
									return;
           						}
       						}		 
           				}	
    				}
       			}   
   			}
			//TEST 3 - checking no of clues < 17
         	for (i = 0; i < 9; i++)
         	{
         		for (j = 0; j < 9; j++)
				{
					if (input[i][j] != 0)
						c++;
				}
			}
			if (c < 17)
				cout<<"\nNumber of clues < 17....Not uniquely solvable!\n\n";
        }
        
        void increment(int cord[] , int ins)
		{
			if(ins == 1)						//move ahead
			{
                if(cord[1] < 8)
                    cord[1]++;					//move to next col
                else
				{
                    cord[1] = 0;
                    cord[0]++;					//move to next row
                }
            }
            else								//move back
			{
                if(cord[1] > 0)
                    cord[1]--;					//move to prev col
                else
				{
                    cord[1] = 8;
                    cord[0]--;					//move to prev row
               	}
            }
        }
        
		int checker(int cord[] , int val)
		{
            int i,j;
            
            for(i = 0; i < 9; i++)
			{
                if(sudoku[i][cord[1]] == val && i != cord[0]) 	//check cols
                    return 1;
            }
            
            for(j = 0; j < 9; j++)
			{
                if(sudoku[cord[0]][j] == val && j != cord[1])   //check rows
                    return 1;
            }

            int x = cord[0] - (cord[0] % 3);
            int y = cord[1] - (cord[1] % 3);

            for(i = x; i < x + 3; i++)							//checking box
			{
                for(j = y; j < y + 3; j++)
				{
                    if(sudoku[i][j] == val && (i != cord[0] && j != cord[1]))
                        return 1;
                }
            }
            return 0;
        }
        
        void solver()
		{ 
            int position[2] = {0,0};							//storing (row,col)
            int temp,i,j;

			while(position[0] > -1 && position[0] < 9)			//runs till row indices in grid are in [0,8]
			{
                if(input[position[0]][position[1]] != 0)		//clue exists
				{
                    increment(position,1);
                    continue;
                }
                
                temp = sudoku[position[0]][position[1]] + 1;	//no. to be placed in cell
                
                while(checker(position,temp) == 1)				//while temp cannot be placed in the cell, increment it
                    temp++;
                
				if(temp < 10)
				{
                    sudoku[position[0]][position[1]] = temp;
                    increment(position,1);
                    continue;
                }
                else											//backtrack
				{
                    sudoku[position[0]][position[1]] = 0;
                    increment(position,0);
                	
				    while(input[position[0]][position[1]] != 0 && position[0] > -1)
                        increment(position,0);
                }
            }
        }
        
        void sample(int c)
		{
            error = 0;
			fstream file;
            
            switch(c)
            {
            	case 1:
            	{
            		file.open("s1.txt" , ios::in);
					break;	
				}
				case 2:
				{
					file.open("s2.txt" , ios::in);
					break;
				}
				case 3:
				{
					file.open("s3.txt" , ios::in);
					break;
				}
				case 4:
				{
					file.open("s4.txt" , ios::in);
					break;
				}
				case 5:
				{
					file.open("s5.txt" , ios::in);
					break;
				}
				
				default:
				{
					error = 1;
					return;
				}
			}
            
			cout<<"\nDifficulty Level "<<c<<" Sudoku : \n---------------------------\n";
			int i,j;
			
            for(i = 0; i < 9; i++)
			{
                for(j = 0; j < 9; j++)		//reading sudoku rowise from file
				{ 
					file>>input[i][j];
					sudoku[i][j] = input[i][j];
                }
            }
            
        	display();
            solver();
            file.close();
        }
        
        void user_soln()
		{
			int i,j;
			for (i = 0; i < 9; i++)			//taking user soln rowise
			{
				for (j = 0; j < 9; j++)
					cin>>input[i][j];
			}
		}    
		    
        void soln_check()
        {
        	int i,j,x,truth = 1;
        	char *correct = "\tCongratulations! Your solution is CORRECT! :)";
        	char *wrong = "\tYour solution is INCORRECT! :(";
			
			for(i = 0; i < 9; i++)
			{
            	for(j = 0; j < 9; j++)
				{ 
                	if(input[i][j] != sudoku[i][j])
					{
						truth = 0;
                    	break;
                	}
            	}
            	if(truth == 0)
                	break;
        	}
        	
			if(truth)
			{
				cout<<setw(45);
				showString(correct);
				cout<<setw(73)<<"\t WELL DONE!\n";
			}
            	
        	else
            {
            	cout<<setw(52); showString(wrong);
				cout<<setw(69)<<"\t   Error at row "<<i+1<<", column "<<j+1<<"\n";
				char *presenting = "Here's the correct solution : "; showString(presenting);
				display();
				char *better = "Better luck next time...\n"; showString(better);
			}
		}
        
        void display()
		{
			cout<<setw(85)<<"-------------------------\n"<<setw(61);
			
			for (int i = 0; i < 9; i++)
			{
				cout<<"| ";
				for (int j = 0; j < 9; j++)
				{
					if (j == 2 || j == 5)
					{
						if (sudoku[i][j] == 0)
							cout<<'.'<<" | ";
						else
							cout<<sudoku[i][j]<<" | ";	
					}
						
					else
					{
						if (sudoku[i][j] == 0)
							cout<<'.'<<" ";
						else
							cout<<sudoku[i][j]<<" ";	
					}
				}
				
				if (i == 2 || i == 5)
					cout<<"|\n"<<setw(85)<<"|-----------------------|\n"<<setw(61);
				else
					cout<<"|\n"<<setw(61);
			}
			cout<<setw(85)<<"-------------------------\n";
        }
        
        void save(clock_t t)			//to append sudoku & its solution to a file based on the time spent to solve it
		{
            fstream file;
            int i,j;
            
            if (t < 1300)
            	file.open("Normal level.txt", ios::app|ios::out);
            
            else if (t > 1300 && t < 2500)
            	file.open("Medium level.txt", ios::app|ios::out);
            	
			else
            	file.open("Hard level.txt", ios::app|ios::out);
            
			file<<"Sudoku "<<c<<": \n";
			
			file<<"-------------------------\n";
			for (int i = 0; i < 9; i++)
			{
				file<<"| ";
				for (int j = 0; j < 9; j++)
				{
					if (j == 2 || j == 5)
					{
						if (input[i][j] == 0)
							file<<'.'<<" | ";
						else
							file<<input[i][j]<<" | ";	
					}
					else
					{
						if (input[i][j] == 0)
							file<<'.'<<" ";
						else
							file<<input[i][j]<<" ";		
					}
					
				}
				if (i == 2 || i == 5)
					file<<"|\n"<<"|-----------------------|\n";
				else
					file<<"|\n";
			}
			file<<"-------------------------\n";
			
            file<<"\nSolution : \n";
            
            file<<"-------------------------\n";
			for (int i = 0; i < 9; i++)
			{
				file<<"| ";
				for (int j = 0; j < 9; j++)
				{
					if (j == 2 || j == 5)
					{
						if (sudoku[i][j] == 0)
							file<<'.'<<" | ";
						else
							file<<sudoku[i][j]<<" | ";	
					}
					else
					{
						if (sudoku[i][j] == 0)
							file<<'.'<<" ";
						else
							file<<sudoku[i][j]<<" ";		
					}
					
				}
				if (i == 2 || i == 5)
					file<<"|\n"<<"|-----------------------|\n";
				else
					file<<"|\n";
			}
			file<<"-------------------------\n";
            
            file<<"\n\n";
            c++;
            file.close();
        }
};

int main()
{
    int i,j,choice;
    
    char *welcome = "Welcome to the SUDOKU SOLVER and CHECKER";
    char *credits = "Prepared by Saksham Koul";
    char *menu = "Game Menu :";
	char *option1 = "1. Enter a sudoku to be solved by the program.";
    char *option2 = "2. Solve a sudoku given by the program.";
    char *option3 = "3. Exit.";
	
	cout<<setw(55); showString(welcome); 
	cout<<setw(56); showString(credits); 
	cout<<"------------------------------------------------------------------------------------------------------------------------------------------------------\n";
	
	while(1)
	{
		showString(menu); cout<<"-----------\n\n";
		showString(option1);
		showString(option2);
		showString(option3);
	
		cout<<"\nEnter your choice : "; cin>>choice;
    	cout<<"\n";

    	Sudoku mysudoku;
    
    	switch(choice)
    	{
    		case 1:
    		{
    			char *solver = "  SUDOKU SOLVER ";
    			cout<<setw(82);
				cout<<"-----------------\n"; 
				cout<<setw(65); showString(solver);
				cout<<setw(82);
				cout<<"-----------------\n";
    		
				char *enter = "\t\t  Enter the sudoku you want the program to solve. Write it row by row, and to indicate a blank cell, enter 0.\n";
    			showString(enter);
        	
				mysudoku.takeinput();
				
        		if (error)
        		{
        			cout<<"\nInvalid sudoku entered!\n";
        			break;
				}
				
				char *entered = "\nYou entered : "; showString(entered);
        		mysudoku.showInput();
        		
        		clock_t t = clock();
        		
        		mysudoku.solver();
        		char *solution = "\n\nSolution to entered sudoku : "; showString(solution);
        		mysudoku.display();
        	
        		t = clock() - t;
        		mysudoku.save(t);
        		
				break;	
			}
		
			case 2:
			{
				int diff, sol;
				char *checker = " SUDOKU CHECKER ";
				cout<<setw(82);
				cout<<"------------------\n"; 
    			cout<<setw(65); showString(checker);
    			cout<<setw(82);
				cout<<"------------------\n"; 
			
	        	char *difficulty = "\t\t\t\t\tI have sudokus of difficulty level from 1(easiest) to 5(hardest).";
    	    	showString(difficulty);
    	    	cout<<"\nEnter the difficulty level you wish to solve : ";
        		cin>>diff;
        
				mysudoku.sample(diff);
				
				if (error)
				{
					cout<<"\nInvalid choice! Try again.";
					break;
				}
				
				cout<<"\nPress : \n";
				char *solve_options = "-> 1 to enter your solution.\n-> 2 to view the solution.\n-> Any other key to go back to main menu.";
				showString(solve_options);
				cout<<"\nYour choice : ";
    	    	
    	    	cin>>sol;
    	    	switch(sol)
    	    	{
    	    		case 1:
    	    		{
    	    			char *enter_sol = "\nEnter your solution row by row : \n"; showString(enter_sol);
						mysudoku.user_soln();
	        			
						char *entered = "\nYou entered : "; showString(entered);
        				mysudoku.showInput();
        		
        				mysudoku.soln_check();
        				break;
					}
					case 2:
					{
						cout<<"\nSolution to Difficulty Level "<<diff<<" sudoku : \n";
    	    			cout<<"---------------------------------------\n";
    	    			mysudoku.display();
    	    			break;
					}
					default:
					{
						char *loading = "\nLoading main game menu...";
						showString(loading);
						Sleep(1000);
					}
				}
            	break;
			}
		
			case 3:
			{
				char *thanks = "  Thanks for playing.";
				cout<<setw(62); showString(thanks);
				exit(0);
			}
		
			default:
				cout<<"Enter valid choice out of the above options!\n\n";
		}
		cout<<endl;
		cout<<setw(80); cout<<"-x-x-x-x-x-x-\n\n";
	}
    return 0;
}
