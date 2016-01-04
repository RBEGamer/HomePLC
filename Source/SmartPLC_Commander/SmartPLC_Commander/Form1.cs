using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Windows.Forms;
namespace SmartPLC_Commander
{




    public partial class Form1 : Form
    {
        Graphics graphics;
        Image render_image;


        List<node> loaded_nodes = new List<node>();
        List<node> schematic_nodes = new List<node>();
        TreeNode selected_treeview_node = new TreeNode();
        string loaded_node_list = "";
        int nid_counter = 1;
        Bitmap drawing_bitmap = new Bitmap(500, 500);

        public Form1()
        {
            InitializeComponent();

            selected_history_tree_node = null;
            selected_treeview_node = null;
            timer1.Enabled = false;



            drawing_bitmap = new Bitmap(500, 500);
            graphics = Graphics.FromImage(drawing_bitmap);

            //create bitmap
            //create hwnd
            //create instance

        }



        //LOADED NODE TREEE VIEW
        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            selected_treeview_node = e.Node;
        }



        //LOAD NODE CONFIG
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

                        if (treeView1.Nodes["__cat__" + splitted_content[3]] == null)
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
                        tnode.description = splitted_content[13];
                        tnode.param_properties = splitted_content[12];
                        tnode.output_con_string = splitted_content[11];
                        tnode.input_con_string = splitted_content[10];
                        tnode.idnr = i;
                        tnode.extention_name = splitted_content[9];
                        loaded_nodes.Add(tnode);



                    }



                }
                catch (Exception)
                {
                    MessageBox.Show("Error while loading ");

                }

            }
        }
        //SAVE NODE CONFIG
        private void saveNodeSchematicToolStripMenuItem_Click(object sender, EventArgs e)
        {
            

            //1:0:2:0%


            string final_string = "<?xml version=\"1.0\"?><info schematic-list=\"" + loaded_node_list + "\" date=\"" + System.DateTime.UtcNow.ToString() + "\" /><schematic>";
            foreach (node n in schematic_nodes)
            {
                //GENERATE CONNECTION STRING
                string constring_tmp = "";
                for (int i = 0; i < connection_list.Count; i++)
                {
                    if (connection_list[i].source.parent_node_id == n.nid) {
                        constring_tmp += connection_list[i].source.parent_node_id.ToString() + ":" + connection_list[i].source.connection_id.ToString() + ":" + connection_list[i].target.parent_node_id.ToString() + ":" + connection_list[i].target.connection_id.ToString() + "%";
                    }
                }
                n.connection_string = constring_tmp;
                //<node nid="6" nsi="ctimest" ncon="6:0:7:0%" nparam="%" />
                final_string += "<node nid=\"" + n.nid + "\" nsi=\"" + n.xml_name + "\" ncon=\"" + constring_tmp + "\" nparam=\"" + n.param_string + "\" pos=\"" + n.pos.x.ToString() + ";" + n.pos.y.ToString() + "\" />";
            }
            final_string += "</schematic>";
            //UPLOAD
            if (!checkBox1.Checked)
            {
                WebRequest upload_request = WebRequest.Create(toolStripTextBox1.Text + "smartsps/upload_schematic.php");
                upload_request.Method = "POST";
                upload_request.Credentials = CredentialCache.DefaultCredentials;
                ((HttpWebRequest)upload_request).UserAgent = "SmartSPS_Commander";
                upload_request.ContentLength = final_string.Length;
                upload_request.ContentType = "text/html";
                upload_request.GetRequestStream().Write(System.Text.Encoding.UTF8.GetBytes(final_string), 0, final_string.Length);
            }
            else
            {
                saveFileDialog1.Filter = "Node Schematic (.xml)|*.xml";
                saveFileDialog1.FilterIndex = 1;


                if (saveFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    System.IO.StreamWriter sw = new System.IO.StreamWriter(saveFileDialog1.FileName);
                    sw.Write(final_string);
                    sw.Close();
                }
            }
            //  MessageBox.Show(final_string);

    

        }

        //LOAD ADDItION NODE CONFIG
        private void loadAdditionalNodeConfigurationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "Implemented Node List (.csv)|*.csv";
            openFileDialog1.FilterIndex = 1;
            openFileDialog1.Multiselect = false;


            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                loaded_node_list += " | " + openFileDialog1.FileName;
                try
                {
                    string[] lines = System.IO.File.ReadAllLines(openFileDialog1.FileName);
                    // treeView1.BeginUpdate();
                    // treeView1.Nodes.Clear();
                    //treeView1.EndUpdate();

                    //loaded_nodes.Clear();
                    //begin loading nodes to tree view
                    //the 1 to skip the headline
                    for (int i = 1; i < lines.Length; i++)
                    {
                        string sel_line = lines[i];
                        string[] splitted_content = sel_line.Split(';');

                        TreeNode tn = new TreeNode();
                        tn.Name = splitted_content[1];
                        tn.Text = splitted_content[2];

                        if (treeView1.Nodes["__cat__" + splitted_content[3]] == null)
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
                        tnode.description = splitted_content[13];
                        tnode.param_properties = splitted_content[12];
                        tnode.output_con_string = splitted_content[11];
                        tnode.input_con_string = splitted_content[10];
                        tnode.extention_name = splitted_content[9];
                        tnode.idnr = i;
                        loaded_nodes.Add(tnode);



                    }



                }
                catch (Exception)
                {
                    MessageBox.Show("Error while loading ");

                }

            }
        }





        //HISTORY TREE VIEW SELECT
        TreeNode selected_history_tree_node = new TreeNode();
        private void treeView2_AfterSelect(object sender, TreeViewEventArgs e)
        {
            selected_history_tree_node = e.Node;
            string nid_string = e.Node.Name.Replace("inst_", "");
            int sel_nid = Int32.Parse(nid_string);
            for (int i = 0; i < schematic_nodes.Count; i++)
            {
                if (schematic_nodes[i].nid == sel_nid)
                {
                    schematic_nodes[i].create_property_plane(ref parameter_panel_form, ref node_title_text, ref node_nid_text, ref node_nsi_text);
                }

            }
        }


        //ADD NODE BTN
        private void button1_Click(object sender, EventArgs e)
        {
            if (selected_treeview_node == null) { return; }
            if (selected_treeview_node.Name.Contains("__cat__")) { return; }
            nid_counter++;
            for (int i = 0; i < loaded_nodes.Count; i++)
            {
                if (loaded_nodes[i].xml_name == selected_treeview_node.Name)
                {
                    node tmnode = loaded_nodes[i];
                    tmnode.nid = nid_counter;
                    tmnode.pos.x = 10;
                    tmnode.pos.y = 10;

                    tmnode.create_connection_list();
                    tmnode.create_drawable(); //actung zuerst create_con_list_aufrufen
                    schematic_nodes.Add(tmnode);

                    // tmnode.create_property_plane(ref parameter_panel_form, ref node_title_text, ref node_nid_text, ref node_nsi_text);
                    TreeNode inst_tree_node_tmp = new TreeNode();
                    inst_tree_node_tmp.Name = "inst_" + tmnode.nid.ToString();
                    inst_tree_node_tmp.Text = selected_treeview_node.Text + ":" + tmnode.nid.ToString();
                    treeView2.Nodes.Add(inst_tree_node_tmp);

                    if (!timer1.Enabled)
                    {
                        timer1.Enabled = true;
                    }
                }
            }
            selected_treeview_node = null;
        }

        //REMOVE NODE BTN
        private void button2_Click(object sender, EventArgs e)
        {
            if (selected_history_tree_node == null) { return; }
            string nid_string = selected_history_tree_node.Name.Replace("inst_", "");
            int sel_nid = Int32.Parse(nid_string);
            for (int i = 0; i < schematic_nodes.Count; i++)
            {
                if (schematic_nodes[i].nid == sel_nid)
                {
                    treeView2.Nodes.Remove(selected_history_tree_node);
                    schematic_nodes.Remove(schematic_nodes[i]);
                }
            }


            selected_history_tree_node = null;
        }

        //DRAWING TIMER
        private void timer1_Tick(object sender, EventArgs e)
        {
            //CLEAR WITH WHITE
            graphics.FillRectangle(Brushes.White, 0, 0, drawing_bitmap.Width, drawing_bitmap.Height);
            //DRAW ALL NODES
            for (int i = 0; i < schematic_nodes.Count; i++)
            {
                schematic_nodes[i].draw_update(ref graphics, new Rectangle(0, 0, drawing_bitmap.Width, drawing_bitmap.Height));
            }

            //DRAW CONNECTION LINES

            for (int j = 0; j < connection_list.Count; j++)
            {
                Point point_source = new Point(connection_list[j].source.drawable_rect.Location.X + connection_list[j].source.drawable_rect.Size.Width, connection_list[j].source.drawable_rect.Location.Y + (connection_list[j].source.drawable_rect.Size.Width / 2));
                Point point_target = new Point(connection_list[j].target.drawable_rect.Location.X, connection_list[j].target.drawable_rect.Location.Y + (connection_list[j].target.drawable_rect.Size.Width / 2));
                Point point_middle = new Point(0, 0);
                if (point_source.X < point_target.X)
                {
                    point_middle.X = point_target.X - point_source.X;
                }
                else
                {
                    point_middle.X = point_source.X - point_target.X;
                }

                if (point_source.Y < point_target.Y)
                {
                    point_middle.Y = point_target.Y - point_source.Y;
                }
                else
                {
                    point_middle.Y = point_source.Y - point_target.Y;
                }

                //NACH TYP
                graphics.DrawBezier(new Pen(connection_list[j].source.con_color), point_source, new Point(point_middle.X, point_source.Y), new Point(point_middle.X, point_target.Y), point_target);
                //connection_list[j].

            }


            //DRAW IMAGE
            pictureBox1.Image = drawing_bitmap;

        }

        //CLAR ALLL BTN
        private void button3_Click(object sender, EventArgs e)
        {
            schematic_nodes.Clear();
            connection_list.Clear();
        }


        Rectangle mouse_pos_rect;
        node drag_node = null;
        Point drag_node_offset = new Point(0, 0);
        node.connection selected_connection = null;
        struct connection_pair
        {
            public node.connection source;
            public node.connection target;
        }
        List<connection_pair> connection_list = new List<connection_pair>();
        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {

            mouse_pos_rect.Location = e.Location;
            mouse_pos_rect.Size = new Size(1, 1);
            if (mouse_pos_rect.IntersectsWith(new Rectangle(0, 0, drawing_bitmap.Width, drawing_bitmap.Height)))
            {

                for (int i = 0; i < schematic_nodes.Count; i++)
                {
                    if (schematic_nodes[i].clipping_recht.IntersectsWith(mouse_pos_rect))
                    {
                        //check if is in base rect
                        if (schematic_nodes[i].base_rect.IntersectsWith(mouse_pos_rect))
                        {
                            selected_connection = null;
                            drag_node = schematic_nodes[i];
                            drag_node_offset.X = (schematic_nodes[i].pos.x - mouse_pos_rect.Location.X);
                            drag_node_offset.Y = (schematic_nodes[i].pos.y - mouse_pos_rect.Location.Y);
                            //switch to property plane
                            drag_node.create_property_plane(ref parameter_panel_form, ref node_title_text, ref node_nid_text, ref node_nsi_text);
                            tabControl1.SelectedIndex = 2;
                        }
                        else
                        {
                            //check if mouse on a connector
                            for (int j = 0; j < schematic_nodes[i].connections.Count; j++)
                            {
                                if (schematic_nodes[i].connections[j].drawable_rect.IntersectsWith(mouse_pos_rect))
                                {

                                    //WENN NICHT LERR DANN VERBINFUNG MACHEN
                                    if (selected_connection == null)
                                    {
                                        selected_connection = schematic_nodes[i].connections[j];
                                    }
                                    else
                                    {

                                        node.connection second_clicked_connection = schematic_nodes[i].connections[j];
                                        if (second_clicked_connection.con_type == node.type.input && selected_connection.con_type == node.type.output)
                                        {
                                            connection_pair tmp_cpair = new connection_pair();
                                            tmp_cpair.source = selected_connection;
                                            tmp_cpair.target = second_clicked_connection;

                                            bool exits = false;
                                            for (int k = 0; k < connection_list.Count; k++)
                                            {
                                                if (connection_list[k].source.connection_id == tmp_cpair.source.connection_id && connection_list[k].source.parent_node_id == tmp_cpair.source.parent_node_id)
                                                {
                                                    if (connection_list[k].target.connection_id == tmp_cpair.target.connection_id && connection_list[k].target.parent_node_id == tmp_cpair.target.parent_node_id)
                                                    {
                                                        exits = true;
                                                    }
                                                }
                                            }

                                            if (!exits)
                                            {
                                                connection_list.Add(tmp_cpair);
                                            }
                                        }
                                        else if (second_clicked_connection.con_type == node.type.output && selected_connection.con_type == node.type.input)
                                        {

                                            connection_pair tmp_cpair = new connection_pair();
                                            tmp_cpair.source = second_clicked_connection;
                                            tmp_cpair.target = selected_connection;
                                            bool exits = false;
                                            for (int k = 0; k < connection_list.Count; k++)
                                            {
                                                if (connection_list[k].source.connection_id == tmp_cpair.source.connection_id && connection_list[k].source.parent_node_id == tmp_cpair.source.parent_node_id)
                                                {
                                                    if (connection_list[k].target.connection_id == tmp_cpair.target.connection_id && connection_list[k].target.parent_node_id == tmp_cpair.target.parent_node_id)
                                                    {
                                                        exits = true;
                                                    }
                                                }
                                            }

                                            if (!exits)
                                            {
                                                connection_list.Add(tmp_cpair);
                                            }
                                        }

                                        selected_connection = null;
                                    }


                                }
                            }
                        }
                    }
                }

            }
            //create 1x1 mouse click rect
            //fist is mouse on image
            //deltapos von der geklickten zur xy des nodes dmit es nicht springt


        }

        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            if (drag_node != null)
            {
                mouse_pos_rect.Location = e.Location;

                drag_node.pos.x = mouse_pos_rect.X + drag_node_offset.X;
                drag_node.pos.y = mouse_pos_rect.Y + drag_node_offset.Y;
                drag_node.create_drawable();
                // drag_node_offset
            }
        }

        private void pictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            drag_node = null;
        }

        private void pictureBox1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            mouse_pos_rect.Location = e.Location;
            mouse_pos_rect.Size = new Size(1, 1);
            if (mouse_pos_rect.IntersectsWith(new Rectangle(0, 0, drawing_bitmap.Width, drawing_bitmap.Height)))
            {

                for (int i = 0; i < schematic_nodes.Count; i++)
                {
                    if (schematic_nodes[i].clipping_recht.IntersectsWith(mouse_pos_rect))
                    {

                        //check if mouse on a connector
                        for (int j = 0; j < schematic_nodes[i].connections.Count; j++)
                        {
                            if (schematic_nodes[i].connections[j].drawable_rect.IntersectsWith(mouse_pos_rect))
                            {
                                node.connection tmp_con = schematic_nodes[i].connections[j];

                                for (int k = 0; k < connection_list.Count; k++)
                                {
                                    if(tmp_con.con_type == node.type.output) {
                                        if(tmp_con.connection_id == connection_list[k].source.connection_id && tmp_con.parent_node_id == connection_list[k].source.parent_node_id)
                                        {
                                            connection_list.Remove(connection_list[k]);
                                        }
                                    }else if (tmp_con.con_type == node.type.input)
                                    {
                                        if (tmp_con.connection_id == connection_list[k].target.connection_id && tmp_con.parent_node_id == connection_list[k].target.parent_node_id)
                                        {
                                            connection_list.Remove(connection_list[k]);
                                        }
                                    }

                                }


                            }
                        }

                            }
                        }
            }

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            
            //download current schematic
            //parse
            //instante all nodes with right values for variables
            //call create drawabel
            //load parameters
            //create_connection_list
        }

        private void toolStripMenuItem2_Click(object sender, EventArgs e)
        {
            string schem_content = "";

            openFileDialog1.Filter = "Node-Schematic (.xml)|*.xml";
            openFileDialog1.FilterIndex = 1;
            openFileDialog1.Multiselect = false;


            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                if(openFileDialog1.FileName == "") { MessageBox.Show("enter valid file"); return; }

              
                try
                {
                    schem_content = System.IO.File.ReadAllText(openFileDialog1.FileName);
                }
                catch (Exception)
                {

                    MessageBox.Show("ERROR WHILE LOADING");
                }
         
            }


            if(schem_content == "")
            {
                return;
            }


            if (!schem_content.StartsWith("<?xml version=\"1.0\"?>")) { MessageBox.Show("StartWith - FAIL"); return; }
            bool schem_starts = false;
            int schem_count = 0;
            string[] split_xml = schem_content.Split('<');

            for (int i = 0; i < split_xml.Length; i++)
            {
                if (split_xml[i].StartsWith("?xml")) { /* XML HEAD */}

                if (split_xml[i].StartsWith("info")) { /* XML INFO HEAD */}

                if (split_xml[i].StartsWith("schematic")) { /*Start schem */schem_starts = true; }

                if (split_xml[i].StartsWith("/schematic")) { /*end schem */schem_starts = false; schem_count++; }

                if (split_xml[i].StartsWith("node") && schem_starts) {
                    /* NODE CONTENT */

                    int start_exp_pos = split_xml[i].IndexOf("nid=\"");
                    int end_exp_pos = split_xml[i].IndexOf("\" ", start_exp_pos+1);
                   
                    string extr_value = split_xml[i].Substring(start_exp_pos, end_exp_pos);
                }

            }



            //    saveFileDialog1.Filter = "Node Schematic (.xml)|*.xml";
            // saveFileDialog1.FilterIndex = 1;

            //download schematic y
            //instnace nodes
            //wen pos nicht bekannt dann 10;10
            //create_connectreions // create drawable // aufrufen

        }


        public void reconstruct_connections()
        {
            //durch alle nodes -> alle con strings und in die connection list einfügen
        }
    }
}
