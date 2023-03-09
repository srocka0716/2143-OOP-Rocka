/*****************************************************************************
*
*  Author:           Sum'r Rocka
*  Title:            Overloaded Operators for Singly Linked List
*  Course:           2143
*  Semester:         Spring 2023
*
*  Description:
*        While using the code written by Dr. Griffin in class, this program allows
*        the user to create nodes and edges with various attributes, that are graphviz legal,
*        that will print to the console and output file to be copied over to GraphViz online
*        to visualize a graph. 
*
*
*  Usage:
*          GraphViz G("LinkedList", "LL");
*   
*          map<string, string> Box;
*          map<string, string> Arrow;
*          Box["shape"] = "box";
*          Box["color"] = "blue";
*          Box["opacity"] = "0.8";
*          A.addAttributes(Box);**
*
*          Arrow["color"] = "black";
*          Arrow["arrowhead"] = "vee";
*          Arrow["arrowtail"] = "dot";
*          A.addAttributes(Arrow);
*
*          int nodeId;
*
*          nodeId = G.addNode(Box);
*          nodeId = G.addNode(Box);
*          G.addEdge(0, 1, Arrow);
* 
*          G.printGraph(G);
*
*
*  Files: Source.cpp    :  Contains GraphViz, Attribute, Edge, Node, Shape claases, and main.
*****************************************************************************/


#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

/**
 * Attribute
 *
 * Description:
 *      This class implements methods to add attributes to the map<string, string>.
 *
 * Public Methods:
 *
 *		void                 addAttribute(string key, string val) { att[key] = val; }
 *      void                 addAttributes(map<string, string> atts)
 *      friend ostream       &operator<<(ostream &os, Attribute &e)
 *      friend fstream       &operator<<(fstream &fout, Attribute &e)
 * 
 * Usage:
 *
 *    
 */
class Attribute
{
protected:
    map<string, string> att; // attributes

public:
    Attribute() {}

    /**
     * Very basic print method to print out some graphviz style
     * code defining an edge.
     */
    // string print() {
    //   return "[color=" + att["color"] + ",arrow_type=" + att["arrow_type"] +
    //   "]";
    // }
    /**
     * Update an edge attribute. Assumes key is valid.
     */
    void addAttribute(string key, string val) { att[key] = val; }

    /**
     * Takes a map of attributes. Loops over them and saves them
     * locally.
     */
    void addAttributes(map<string, string> atts)
    {
        for (auto const &x : atts)
        {
            cout << x.first << "=" << x.second << endl;
            att[x.first] = x.second;
        }
    }

    /**
     * Use our basic print to dump this class out.
     */
    friend ostream &operator<<(ostream &os, Attribute &e)
    {

        os << "[";

        int i = 0;
        for (auto const &x : e.att)
        {
            os << x.first << "="
               << "\"" << x.second << "\"";

            if (i < e.att.size() - 1)
            {
                os << ", ";
            }
            i++;
        }
        os << "]";

        return os;
    }

    /**
      * Public : operator<<
      *
      * Description:
      *      Overloads the << operator to be able to print out edges to output file.
      *
      * Params:
      *           Attribute &    : attributes passed in that will be printed out
      *      const ostream  &    : The output stream
      */
    friend fstream &operator<<(fstream &fout, Attribute &e)
    {

        fout << "[";
        int i = 0;
        for (auto const &x : e.att)
        {
            fout << x.first << "="
                 << "\"" << x.second << "\"";
            if (i < e.att.size() - 1)
            {

                fout << ", ";
            }
            i++;
        }

        fout << "]";
        return fout;
    }
};

/**
 * Edge
 *
 * Description:
 *      This class implements methods to create new edges using constructors. Also has
 *      method that overloads ostream.
 *
 * Public Methods:
 *
 *		Edge                ()
 *      Edge                (string color, string arrow)
 *      Edge                (int start, int end)
 *      friend ostream      &operator<<(ostream &os, Edge &e)
 *
 * Usage:
 *
 */
class Edge : public Attribute
{
    int eid;
    int start;
    int end;

public:
    /**
    * Public : Edge
    *
    * Description:
    *      Default constructor that sets the color and arrow type as default types.
    */
    Edge()
    {
        att["color"] = "black";    // default color
        att["arrow_type"] = "vee"; // default arrow shape
    }

    /**
    * Public : Edge
    *
    * Description:
    *      Constructor that takes in user input for style of edge
    *
    * Params:
    *      string color        : The string that will store the color of edge
    *      string arrow        : String that will store arrow type
    * Returns:
    *     MyVector V           : The new vector containing the difference of two lists
    */
    Edge(string color, string arrow)
    {
        att["color"] = color;      
        att["arrow_type"] = arrow; 
    }
    /**
    * Public : Edge
    *
    * Description:
    *      Is a constructor that allows for creation of an edge
    *
    * Params:
    *      int start           : The beginning edge
    *      int end             : The edge it is pointing to
    */
    Edge(int start, int end)
    {
        this->start = start;
        this->end = end;
    }

    /**
    * Public : operator<<
    *
    * Description:
    *      Overloads the << operator to be able to print out edges to ostream.
    *
    * Params:
    *                Edge &    : edge passed in that will be printed out
    *      const ostream  &    : The output stream
    */
    friend ostream &operator<<(ostream &os, Edge &e)
    {
        os << e.start << "->" << e.end << " ";
        os << "[";

        int i = 0;
        for (auto const &x : e.att)
        {
            os << x.first << "="
               << "\"" << x.second << "\"";

            if (i < e.att.size() - 1)
            {
                os << ", ";
            }
            i++;
        }
        os << "]";

        return os;
    }
};

/**
 * Node
 *
 * Description:
 *      This class has two construcors that create a node with either two default vaules
 *      or values that the user brings in.
 *
 * Public Methods:
 *
 *		Node()
 *      Node(map<string, string> atts)
 *
 * Usage:
 *
 *    
 */
class Node : public Attribute
{
    int nid;

public:
    /**
   * Public : Node
   *
   * Description:
   *      Default constructor that sets the color and shape as defaults.
   */
    Node()
    {
        att["color"] = "black";  // default color
        att["shape"] = "record"; // default arrow shape
    }

    /**
    * Public : Edge
    *
    * Description:
    *      Is a constructor that allows for creation of a node
    *      with a set of attributes that are passed in from a
    *      map.
    *
    * Params:
    *     map<string, string> atts           : The map the constructor will loop over
    */
    Node(map<string, string> atts)
    {
        for (auto const &x : atts)
        {
            att[x.first] = x.second;
        }
    }
};

struct Shape
{
    string shape;
    Shape(string name) { shape = name; }
};

/**
 * Graphviz
 *
 * Description:
 *      This class implements methods in order to generate graphs in graphviz to
 *      visualize graphs the user creates.
 *
 * Public Methods:
 *
 *		GraphViz            ()
 *      GraphViz            (string graph_name, string graph_shape)
 *      int                 addNode()
 *      int                 addNode(map<string, string> atts)
 *      void                updateNode(int id, string key, string value)
 *      void                addEdge(int start, int end)
 *      void                addEdge(int start, int end, map<string, string> att)
 *      void                printGraph(string graphName = "")
 *      friend              ostream &operator<<(ostream &os, GraphViz &g)
 *
 */
class GraphViz
{
    int edgeId;
    int nodeId;
    vector<Edge> Edges;
    vector<Node> Nodes;
    string graphName;
    string graphShape;

    //string makeEid(int v, int w) { return to_string(v) + "-" + to_string(w); }


public:
    /**
    * Public : GraphViz
    *
    * Description:
    *      Default constructor that sets the edgeId, nodeId, and graphName.
    */
    GraphViz()
    {
        edgeId = 0;
        nodeId = 0;
        graphName = "foo";
    }

    /**
   * Public : GraphViz
   *
   * Description:
   *      Constructor that takes in graph name and graph shape from user input.
   *
   * Params:
   *    string graph_name      :  user input graph name
   *    string graph_shape     :  user input graph shape
   */
    GraphViz(string graph_name, string graph_shape)
    {
        edgeId = 0;
        nodeId = 0;
        graphName = graph_name;
        graphShape = graph_shape;
    }

    /**
  * Public : addNode
  *
  * Description:
  *      Adds a new node to the graph by creating and adding a node to Nodes.
  * Returns:
  *       Nodes.size() - 1, the index of the new node
  */
    int addNode()
    {
        Nodes.push_back(Node());
        return Nodes.size() - 1;
    }

    /**
    * Public : addNode
    *
    * Description:
    *      Adds a new node to the graph by creating and adding a node to Nodes
    *      using attributes in the atts map.
    * Parameters:
    *           map<string, string> atts           : what attributes the node will be created with
    *           
    * Returns:
    *       Nodes.size() - 1, the index of the new node
    */
    int addNode(map<string, string> atts)
    {
        Nodes.push_back(Node(atts));

        return Nodes.size() - 1;
    }

    /**
  * Public : uodateNode
  *
  * Description:
  *      Is used for updating attributes of a node 
  *
  * Params:
  *     int id          : index of the node going to be updated
  *     string key      : attribute name
  *     string value    : what the attribute will become
  */
    void updateNode(int id, string key, string value)
    {
        Nodes[id].addAttribute(key, value);
    }

    /**
  * Public : addEdge
  *
  * Description:
  *      adds a new edge
  *
  * Params:
  *    int start     : starting edge
  *    int end       : ending edge
  */
    void addEdge(int start, int end)
    {
        Edges.push_back(Edge(start, end));
    }

    /**
  * Public : addEdge
  *
  * Description:
  *      Is a constructor that allows for creation of a node
  *      with a set of attributes that are passed in from a
  *      map.
  *
  * Params:
  *      int start                 : starting edge
  *      int end                   : ending edge
  *       map<string, string> att  :
  */
    void addEdge(int start, int end, map<string, string> att)
    {

        Edges.push_back(Edge(start, end));
        Edges[Edges.size() - 1].addAttributes(att);
    }

    // output your graphviz stuff
    void printGraph(string graphName = "")
    {
        if (graphName.size() == 0)
            graphName = this->graphName;

        cout << "digraph" << graphName << "{";
        // loop over nodes and print them
        for (int i = 0; i < Nodes.size(); i++)
        {
            cout << i << " " << Nodes[i] << endl;
        }
        // loop over edges and print them
        cout << "}\n";
    }

    friend ostream &operator<<(ostream &os, GraphViz &g)
    {
        for (int i = 0; i < g.Nodes.size(); i++)
        {
            os << i << " " << g.Nodes[i] << endl;
        }
        for (int i = 0; i < g.Edges.size(); i++)
        {
            os << g.Edges[i] << endl;
        }
        return os;
    }
};


int main()
{
    ofstream fout;
    fout.open("test.out");

    fout << "Sum'r Rocka" << endl;
    fout << "3/9/2023" << endl;
    fout << "Spring 2143" << endl << endl;

    //completely honest, I couldn't figure out how to do the records in a timely manor
    //so this is just me throwing attributes into a new graph
    // create graphviz instances with specific shapes
    GraphViz G("LinkedList", "LL");
    GraphViz T("failing", "LL");
    GraphViz M("RecordAttempt", "LL");


    // used as an example to load attributes for a node
    map<string, string> Box;
    map<string, string> Arrow;

     //example attribute that gets a map of attributes and
     //adds them to "A"
    Attribute A;
    Box["shape"] = "box";
    Box["color"] = "darkslateblue";
    Box["fontcolor"] = "blue";
    Box["opacity"] = "0.8";
    Box["style"] = "filled";
    Box["fillcolor"] = "orange";
    A.addAttributes(Box);

    Arrow["color"] = "black";
    Arrow["arrowhead"] = "vee";
    Arrow["arrowtail"] = "dot";
   /* A.addAttributes(Arrow);*/

    int nodeId;


    Attribute S;
    map<string, string> Star;

    Star["shape"] = "star";
    Star["color"] = "turquoise";
    Star["fontcolor"] = "darkolivegreen3";
    Star["opacity"] = "0.8";
    Star["style"] = "filled";
    Star["fillcolor"] = "darkgreen";
  
    S.addAttributes(Star);
    S.addAttributes(Arrow);

    //just brute forcing this 
    fout << "digraph failing{\n"
        << "rankdir = LR;\n ";
    cout << "digraph failing{\n"
        << "rankdir = LR;\n ";

    nodeId = T.addNode(Star);
    nodeId = T.addNode(Star);
    nodeId = T.addNode(Star);
    nodeId = T.addNode(Star);
    nodeId = T.addNode(Box);
    T.addEdge(0, 1, Arrow);
    T.addEdge(1, 2, Arrow);
    T.addEdge(2, 3, Arrow);
    T.addEdge(3, 4, Arrow);

    cout << T << "}" << endl;
    fout << T << "}" << endl;

    //Attribute R;
    //map<string, string> Record;

    //Record["shape"] = "record";
    //Record["color"] = "turquoise";
    //Record["fontcolor"] = "darkolivegreen3";
    //Record["opacity"] = "0.8";
    //Record["style"] = "filled";
    //Record["fillcolor"] = "darkgreen";
    //Record["label"] = "<data>|<next>";
    ////Record["label"] = "\"<data> | <next>\"";

    //R.addAttributes(Record);
    //R.addAttributes(Arrow);
 
    //fout << "digraph RecordAttempt{\n"
    //    << "rankdir = LR;\n ";
    //cout << "digraph RecordAttempt{\n"
    //    << "rankdir = LR;\n ";

    //nodeId = M.addNode(Record);
    //nodeId = M.addNode(Record);
    //nodeId = M.addNode(Record);
    //nodeId = M.addNode(Record);
    //nodeId = M.addNode(Box);
    //M.addEdge(0, 1, Arrow);
    //M.addEdge(1, 2, Arrow);
    //M.addEdge(2, 3, Arrow);
    //M.addEdge(3, 4, Arrow);

    //cout << M << "}" << endl;
    //fout << M << "}" << endl;
}

