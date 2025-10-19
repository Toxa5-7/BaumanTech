#include <iostream>
#include<vector>
int main()
{
    std::vector<std::vector<int>> triangle ={{-1}, {2, 3}, {1, -1, -3}, {4, 2, 1, 3}};
    std::vector<std::vector<int>> each_sum = triangle;   //запись суммы до каждого элемента
    std::vector<std::vector<int>> idx_for_path(triangle.size(), std::vector<int>(triangle.size(), 0));    //для записи индексов минимального пути

    for (size_t i = 1; i < triangle.size(); i++)    //вершина исходная
                                                    //O(n^2)
    {
        for (size_t j = 0; j <=i; j++)
        {
            if(j==0)
            {
                each_sum[i][j] += each_sum[i-1][j];
                idx_for_path[i][j] = j; // i на i 
                //std::cout<<triangle[i][j]<<std::endl;
                
            }
            else if (j == i) 
            {
                each_sum[i][j] += each_sum[i-1][j-1];
                idx_for_path[i][j] = j-1; // i на i+1
            }
            else{
                if (each_sum[i-1][j-1] < each_sum[i-1][j]) 
                {
                    each_sum[i][j] += each_sum[i-1][j-1];
                    idx_for_path[i][j] = j-1;
                    
                } 
                else {
                    each_sum[i][j] += each_sum[i-1][j];
                    idx_for_path[i][j] = j;
                }
            }
            
            
        }
        
    }


    int min_sum = each_sum[triangle.size()-1][0], min_idx = 0;

    for (int i = 1; i < triangle.size(); i++) 
    {
        if (each_sum[triangle.size()-1][i] < min_sum) 
        {
            min_sum = each_sum[triangle.size()-1][i]; //
            min_idx = i;
           // std::cout<<min_sum<<' '<<min_idx<<std::endl;
        }
    }

    std::vector<int> min_path(triangle.size()); //для вывода пути поэлементно
    int idx = min_idx;
    for (int i = triangle.size()-1; i >= 0; --i) {
        min_path[i] = triangle[i][idx];
        idx = idx_for_path[i][idx];
    }
    

    std::cout << "Min distance: ";
    for (int i = 0; i < triangle.size(); i++) {
        std::cout << min_path[i];
        if (i + 1 < triangle.size())
            std::cout << " -> ";
    }

    std::cout <<'\n'<< "Result: " << min_sum << std::endl;
}

