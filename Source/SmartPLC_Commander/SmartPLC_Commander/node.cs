using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;
namespace SmartPLC_Commander
{
    class node
    {
        public struct transform
        {
           public  int x, y;
        }


        public struct connection
        {
           

            public int x,y;
            int connection_id;
            string description;
            public enum type
            {
                input, output, none
            }
            public type con_type;
        }


        public int idnr;
        public int nid;
        public transform pos;
        public string xml_name;
        public string title;
        public string category;

        public string description;
        public string param_string;
        public string input_con_string;
        public string output_con_string;

        public string param_properties;

        public string connection_string;
        public string extention_name;

        public node(){
            pos = new transform();
            xml_name = "";
            title = "";
            nid = -1;
            category = "";
            description = "";
            param_string = "";
            input_con_string = "";
            output_con_string = "";
            param_properties = "";
            connection_string = "";
            extention_name = "";
    }

      
        public void create_property_plane(ref Panel parameter_panel, ref Label ltitle, ref Label lnid, ref Label lnsi)
        {

            ltitle.Text = title;
            lnid.Text = nid.ToString();
            lnsi.Text = xml_name;
            parameter_panel.Controls.Clear();
            //  List<System.Windows.Forms> forms = new List<System.Windows.Forms>();
            //param_properties auslesen nach [0,type,desc,()]
            //fdazu passend die elementer erstelln und nach 0 anordnen

            if(param_properties == "") { return; } //dan gibts nichts zu laden
            string[] split_comma = param_properties.Split('%');

            for (int i = 0; i < split_comma.Length; i++)
            {
                if(split_comma[i] == "") { break; } //reach end ?
                string param_construct = split_comma[i];
                param_construct =  param_construct.Substring(1, param_construct.Length - 2);
                string[] split_construct = param_construct.Split(','); 

                int param_id = Int16.Parse(split_construct[0]);
                //CREATE LABEL
                Label lable_tmp = new Label();
                lable_tmp.Enabled = true;
                lable_tmp.Location = new Point(6, 25 + (40 * param_id));
                lable_tmp.Text = split_construct[2];
                lable_tmp.Name = "desc_" +param_id.ToString();
                lable_tmp.Size = new Size(60, 13);
                parameter_panel.Controls.Add(lable_tmp);
              




                //string ohne bereich = normale textbox
                if (split_construct[1] == "string" && split_construct.Length == 3)
                {
                    TextBox textbox_tmp = new TextBox();
                    textbox_tmp.Enabled = true;
                    textbox_tmp.Location = new Point(70, 20 + (40 * param_id));
                    textbox_tmp.Size = new Size(100, 20);
                    textbox_tmp.Name = "param_" + param_id.ToString();

                    if (split_construct[2].ToLower().Replace(" ", "") == "msi")
                    {
                        if (extention_name != "") {
                            textbox_tmp.Text = extention_name;
                            textbox_tmp.ReadOnly = true;
                        }
                    }
                    else
                    {
                        textbox_tmp.Text = "";
                    }
                    parameter_panel.Controls.Add(textbox_tmp);
                }
                //string mit breich = combobox
                else if (split_construct[1] == "string" && split_construct.Length == 4 && split_construct[3].Contains(" "))
                {
                    string[] values = split_construct[3].Substring(1, split_construct[3].Length - 2).Split(' ');
                    if (values.Length == 0) { break; }
                    ComboBox tcombp = new ComboBox();
                    tcombp.Enabled = true;
                    tcombp.Name = "param_" + param_id.ToString();
                    tcombp.Size = new Size(100, 20);
                    tcombp.Location = new Point(70, 20 + (40 * param_id));
                    tcombp.Items.AddRange(values);
                    tcombp.SelectedIndex = 0;
                    tcombp.Text = values[0];
                    parameter_panel.Controls.Add(tcombp);
                }

                else if (split_construct[1] == "int" && split_construct.Length == 3)
                {
                    NumericUpDown tnud = new NumericUpDown();
                    tnud.Enabled = true;
                    tnud.Name = "param_" + param_id.ToString();
                    tnud.Size = new Size(100, 20);
                    tnud.Location = new Point(70, 20 + (40 * param_id));
                    if (split_construct[2].ToLower().Replace(" ", "") == "mid")
                    {
                        tnud.Maximum = 65536;
                        tnud.Minimum = 1;
                        tnud.Value = 1;
                    }
                    else {
                        tnud.Maximum = int.MaxValue;
                        tnud.Minimum = int.MinValue;
                        tnud.Value = 0;
                    }
                        

                    
                    
                    tnud.DecimalPlaces = 0;
                    tnud.Increment = 1;
                    parameter_panel.Controls.Add(tnud);
                }
                else if (split_construct[1] == "float" && split_construct.Length == 3)
                {
                    NumericUpDown tnud = new NumericUpDown();
                    tnud.Enabled = true;
                    tnud.Name = "param_" + param_id.ToString();
                    tnud.Size = new Size(100, 20);
                    tnud.Location = new Point(70, 20 + (40 * param_id));
                    tnud.Minimum = decimal.MinValue;
                    tnud.Maximum = decimal.MaxValue;
                    tnud.DecimalPlaces = 1;
                    tnud.Value = new decimal(0.0f);
                    tnud.Increment = new decimal(0.1f);
                    parameter_panel.Controls.Add(tnud);


                }
                else if (split_construct[1] == "int" && split_construct.Length == 4 && split_construct[3].Contains("-"))
                {
                    string[] values = split_construct[3].Substring(1, split_construct[3].Length - 2).Split('-');
                    if (values.Length == 0) { break; }

                    NumericUpDown tnud = new NumericUpDown();
                    tnud.Enabled = true;
                    tnud.Name = "param_" + param_id.ToString();
                    tnud.Size = new Size(100, 20);
                    tnud.Location = new Point(70, 20 + (40 * param_id));
                    tnud.Minimum = Int32.Parse(values[0]);
                    tnud.Maximum = Int32.Parse(values[1]);
                    tnud.Value = Int32.Parse(values[0]);
                    tnud.DecimalPlaces = 0;
                    tnud.Increment = 1;
                    parameter_panel.Controls.Add(tnud);
                }
                else if (split_construct[1] == "float" && split_construct.Length == 4 && split_construct[3].Contains("-"))
                {
                    string[] values = split_construct[3].Substring(1, split_construct[3].Length - 2).Split('-');
                    if (values.Length == 0) { break; }

                    NumericUpDown tnud = new NumericUpDown();
                    tnud.Enabled = true;
                    tnud.Name = "param_" + param_id.ToString();
                    tnud.Size = new Size(100, 20);
                    tnud.Location = new Point(70, 20 + (40 * param_id));
                    tnud.Minimum = new decimal( float.Parse(values[0]));
                    tnud.Maximum = new decimal( float.Parse(values[1]));
                    tnud.Value = new decimal( float.Parse(values[0]));
                    tnud.DecimalPlaces = 1;
                    tnud.Increment = new decimal(0.1f);
                    parameter_panel.Controls.Add(tnud);
                }else if (split_construct[1] == "bool" && split_construct.Length == 3)
                {


                    CheckBox tchbx = new CheckBox();
                    tchbx.Name = "param_" + param_id.ToString();
                    tchbx.Location = new Point(70, 20 + (40 * param_id));
                    tchbx.Enabled = true;
                    parameter_panel.Controls.Add(tchbx);
                }






                //bool checkbox



            } 


                load_parameters(ref parameter_panel);
            if (param_string == "" || !param_string.Contains("%")) {
                save_parameters(ref parameter_panel);
            }
        }

        public void load_parameters(ref Panel param_panel)
        {

            if(param_string == "" || !param_string.Contains("%")) { return; }
            string[] split_param = param_string.Split('%');
            for (int i = 0; i < split_param.Length; i++)
            {
               if( param_panel.Controls["param_" + i.ToString()] != null)
                {

                    //TYPE DIFFERENT
                    param_panel.Controls["param_" + i.ToString()].Text = split_param[i];
                }

            }



            //wenn string != ""
            //durchsteppen und in die boxen schreiben

        }

        public void save_parameters(ref Panel param_panel)
        {
            param_string = "";

            for (int i = 0; i < param_panel.Controls.Count; i++)
            {
                ///LABELS ENTFEREN
                if (param_panel.Controls[i].Name.Contains("param_")) {
                    param_string += param_panel.Controls[i].Text + "%";
                }
                
            }
            if (param_string == "") {
                param_string = "%";
            }
           // MessageBox.Show(param_string);
        }



        public void draw_update()
        {

        }


        Rectangle base_rect = new Rectangle();

        public void create_drawable()
        {
     
           
        }
        public void calc_element_positions()
        {
            //REcht grösse berechnen ->nach anzahl der zeichen in der headline und

            base_rect.Location = new Point(pos.x, pos.y);
            base_rect.Size = new Size(10, 10);
        }
    }
}
