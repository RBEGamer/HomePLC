using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace SmartPLC_Commander
{

 


    public partial class Form1 : Form
    {
        List<node> loaded_nodes = new List<node>();
        List<node> schematic_nodes = new List<node>();
        string loaded_node_list = "";
        int nid_counter = 0;
        public Form1()
        {
            InitializeComponent();
        
        }


        
        
        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            if (e.Node.Name.Contains("__cat__")) { return; }
            nid_counter++;
            for (int i = 0; i < loaded_nodes.Count; i++)
            {
                if(loaded_nodes[i].xml_name == e.Node.Name) {
                    node tmnode = loaded_nodes[i];
                    tmnode.nid = nid_counter;
                    schematic_nodes.Add(tmnode);
                }
            }
        }

        private void nodeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "Implemented Node List (.csv)|*.csv";
            openFileDialog1.FilterIndex = 1;
            openFileDialog1.Multiselect = false;

           
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                loaded_node_list = openFileDialog1.FileName;
                try
                {
                    string[] lines = System.IO.File.ReadAllLines(openFileDialog1.FileName);
                    treeView1.BeginUpdate();
                    treeView1.Nodes.Clear();
                    treeView1.EndUpdate();

                    loaded_nodes.Clear();
                    //begin loading nodes to tree view
                    //the 1 to skip the headline
                    for (int i = 1; i < lines.Length; i++)
                    {
                        string sel_line = lines[i];
                        string[] splitted_content = sel_line.Split(';');

                        TreeNode tn = new TreeNode();
                        tn.Name = splitted_content[1];
                        tn.Text = splitted_content[2];

                        if(treeView1.Nodes["__cat__" + splitted_content[3]] == null)
                        {
                            TreeNode tmp_tn = new TreeNode();
                            tmp_tn.Name = "__cat__" + splitted_content[3];
                            tmp_tn.Text = splitted_content[3];
                            treeView1.Nodes.Add(tmp_tn);
                            treeView1.Nodes["__cat__" + splitted_content[3]].Nodes.Add(tn);
                        }
                        else
                        {
                            treeView1.Nodes["__cat__" + splitted_content[3]].Nodes.Add(tn);
                        }

                        //CREATE PRPERTY CLASS
                        node tnode = new node();
                        tnode.category = splitted_content[3];
                        tnode.xml_name = splitted_content[1];
                        tnode.title = splitted_content[2];
                        tnode.description = splitted_content[12];
                        tnode.param_properties = splitted_content[11];
                        tnode.output_con_string = splitted_content[10];
                        tnode.input_con_string = splitted_content[9];
                        tnode.idnr = i;
                        loaded_nodes.Add(tnode);



                    }



                }
                catch (Exception)
                {
                    MessageBox.Show("Error while loading ");
                    throw;
                }
              
            }
        }

        private void saveNodeSchematicToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string final_string = "<?xml version=\"1.0\"?><info schematic-list=\"" + loaded_node_list + "\" date=\""+ System.DateTime.UtcNow.ToString() +"\" /><schematic>";
            foreach (node n in schematic_nodes)
            {
                //<node nid="6" nsi="ctimest" ncon="6:0:7:0%" nparam="%" />
                final_string += "<node nid=\"" + n.nid +"\" nsi=\""+ n.xml_name +"\" ncon=\""+ n.connection_string +"\" nparam=\""+ n.param_string +"\" />";
            }
            final_string += "</schematic>";


            //UPLOAD
        }
    }
}
