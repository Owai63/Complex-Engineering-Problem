#include<iostream>
#include<sstream>
#include<cstring>
#include<vector>
#include<fstream>
using namespace std;

class Edge{                                       //Class Edge
	private:
		int Weight;
		string start_node,end_node;
	public:
	Edge(){                                       // Default constructor
		Weight=0;
		start_node='\0';
		end_node='\0';
	}
	Edge(int Weight,string start_node,string end_node){  // Perimeterized constructor
		this->Weight=Weight;
		this->start_node= start_node;
		this->end_node=end_node;
	}
	int get_weight(){
		return this->Weight;
	}
	
	string get_start_node(){
	return this->start_node;
	}
	
	string get_end_node(){
	return this->end_node;
	}
	~Edge(){			  	// Destructor
	}	
};
class Node{					// Class Node
	private:
		string Node_Name;
	public:
	Node(){
		Node_Name='\0';
	}
	Node(string Node_Name){
		this->Node_Name=Node_Name;
	}
	string Get_Node(){
		return this->Node_Name;
	}
	~Node(){
	}	
};
string SplitString(const string, const int);
const int returnIndex (  vector <Node> &, const string &);
class Graph{			//Class Graph
	private:
		vector<Node> Nodes;				//vector declaration
		vector<Edge> Edges;
	public:
		Graph(){						//vector construction
			Nodes={};					
			Edges={};
		}
		bool graphtype;
		friend ifstream & operator >> (ifstream &, Graph &);
		friend ofstream & operator << (ofstream &, Graph &);
};
string SplitString(const string StringToSplit, const int PositionToReturn)			//converts Sentences into words
	{
		string buf;
		stringstream ss(StringToSplit);
	
		vector<string> Splits;
	
		while (ss >> buf)
			Splits.push_back(buf);
	
		return Splits[PositionToReturn];
	}
	
	const int returnIndex ( vector <Node> & SourceVector, const string & stringToFind)		// finds a string in an array and returns the index at which it is found
	{
		for (size_t i = 0; i < SourceVector.size() ; i++)
		{
			if ((SourceVector[i].Get_Node())== stringToFind)
			{
				return i;
			}
			else continue;
		}
		return 0;
	}
ifstream & operator >> (ifstream &input, Graph &i_graph){									// reads the input file
		string reading;
		bool Node_Reading = true;
		while (!input.eof())
		{
			getline(input, reading);
			if (reading[0] == ';')
			{
				continue;
			}
			else if (reading.length() == 0)
			{
				Node_Reading = false;
			}
			else
			{
				if (Node_Reading)
				{
					i_graph.Nodes.push_back((SplitString(reading, 1)));					// push_back makes a new node class in node vector
				}
				else
				{
					i_graph.Edges.push_back(Edge (stoi (SplitString(reading, 2)) , SplitString (reading, 0), SplitString (reading, 1)));
				}
			}
		}
		return input;
	}
ofstream & operator << (ofstream &output, Graph &obj){ 					//writes to the output file
		switch(obj.graphtype){
			case true:
			output << "digraph" <<endl;	
			output << "{" <<endl;
			output << "\tgraph[];" <<endl;
			output << endl;
			
			output << "\tnode [fontcolor= black" << ", fontsize= 20" << "];" << endl;
			output << "\tedge [fontsize= 20 "<< ", arrowhead= vee "<< ", arrowsize= 0.5" << "];" << endl;
			output << endl;
	
			for (size_t i = 0; i < obj.Nodes.size() ; i++)				//writes the data of node vector
			{
				output << "\t\"" << i+1 << "\" [label=\"" << obj.Nodes[i].Get_Node() << "\"];" <<endl;
			}
			
			for (size_t i = 0; i < obj.Edges.size() ; i++) 				//writes the data of edge vector
			{
				output << "\t\"" << returnIndex ((obj.Nodes) , (obj.Edges[i].get_start_node() ) )+ 1 << "\" " << "->" << "\"" << returnIndex ((obj.Nodes) , (obj.Edges[i].get_end_node() ) )+ 1 << "\" [label=\"" << obj.Edges[i].get_weight() << "\"];" <<endl;
			}
	
			output << "}" <<endl;
			break;
		case false:
		output << "graph" <<endl;	
		output << "{" <<endl;
		output << endl;
		output << "\tnode [fontcolor= black" << ", fontsize= 20" << "];" << endl;
		output << "\tedge [fontsize= 20 "<< ", arrowhead= vee "<< ", arrowsize= 0.5" << "];" << endl;
		output << endl;

		for (size_t i = 0; i < obj.Nodes.size() ; i++)				//writes the data of node vector
		{
			output << "\t\"" << i+1 << "\" [label=\"" << obj.Nodes[i].Get_Node() << "\"];" <<endl;
		}
		
		for (size_t i = 0; i < obj.Edges.size() ; i++) 				//writes the data of edge vector
		{
			output << "\t\"" << returnIndex ((obj.Nodes) , (obj.Edges[i].get_start_node() ) )+ 1 << "\" " << "--" << "\"" << returnIndex ((obj.Nodes) , (obj.Edges[i].get_end_node() ) )+ 1 << "\" [label=\"" << obj.Edges[i].get_weight() << "\"];" <<endl;
		}

		output << "}" <<endl;
		break;
	}
		return output;
	}
int main(){
	int a;
	Graph G;
	ifstream input_File;
	ofstream output_File;
	input_File.open ("example.txt", ios::in);			// File Handling
	if (input_File.is_open())
	{
		input_File >> G;
		input_File.close();
	}
	int choice;
	cout<<"Select the type of graph: "<<endl;
	cout<<"1: Directed Graph \n";
	cout<<"2: Undirected Graph \n";
	cout<<"choice: ";
	cin>>choice;
	if (choice==1){
		G.graphtype=true;
	}
	else if(choice ==2){
		G.graphtype=false;
	}
	else{
		cout<<"Wrong Input!!";
		return -1;
	}
	
	output_File.open ("Graph Output.dot",ios::out);
	if (output_File.is_open())
	{
		output_File << G;
		output_File.close();
	}
	cout<<"\n Press 1 to get File in png form.";
	cout<<"\n Press 2 to get File in jpg form.\n";
	cin>>a;
	switch(a){
		case 1:
			system ("dot -Tpng \"Graph Output.dot\" -o Print.png");
		break;
		case 2:
			system ("dot -Tpng \"Graph Output.dot\" -o Print.jpg");
	}
	cout<<"The graph is converted sucessfully";
	return 0;
}