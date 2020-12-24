#include <iostream>
#include <vector>
#include <utility>
using namespace std;
int get_parent_index(int child_index,vector<int>&nodes){
  if(nodes[child_index]<0){
    return child_index;
  }
  return get_parent_index(nodes[child_index],nodes);

}
void detect_cycles (int number_of_nodes,vector<pair<int,int>> edges){
  vector<int> nodes(number_of_nodes,-1);
  int first_parent_index,second_parent_index;
  for(pair<int,int> edge:edges){
    // perform Find
    first_parent_index = get_parent_index(edge.first,nodes);
    second_parent_index = get_parent_index(edge.second,nodes);
    // perform collapsed find
    
    if(first_parent_index == second_parent_index){
      cout<<"cycle found in edge ("<<edge.first<<" ,"<<edge.second<<") \n";
    }
    // perform weighted union 

    else if(nodes[first_parent_index]<=nodes[second_parent_index]){
      nodes[first_parent_index]+=nodes[second_parent_index];
      nodes[second_parent_index] = first_parent_index ;
      // perform collapsed find
      if(edge.first!=first_parent_index)
      {
        nodes[edge.first] = first_parent_index;
      }
      nodes[edge.second ] =first_parent_index ;
    }
    else{
      nodes[second_parent_index]+=nodes[first_parent_index];
      nodes[first_parent_index] =second_parent_index;
      // perform collapsed find
      nodes[edge.first] = second_parent_index;
      if(edge.second != second_parent_index){      
        nodes[edge.second ] =second_parent_index ;
      }
    }

  }
}

int main(){
  vector<pair<int,int>> edges ={make_pair(0,1),make_pair(2,3),make_pair(4,5),make_pair(6,7),
  make_pair(1,3),make_pair(1,4),make_pair(0,2),make_pair(5,7),make_pair(4,6)};
  detect_cycles(8,edges);
  return 0;
}