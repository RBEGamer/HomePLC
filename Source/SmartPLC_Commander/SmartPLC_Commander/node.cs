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
           public  float x, y;
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


                // 0 = paramid 
                //1 = typ
                //2 = desc
                //3 = range ()c


                int param_id = Int16.Parse(split_construct[0]);
                //CREATE LABEL
                Label lable_tmp = new Label();
                lable_tmp.Enabled = true;
                lable_tmp.Location = new Point(6, 25 + (40 * param_id));
                lable_tmp.Text = split_construct[2];
                lable_tmp.Name = "desc_param_" +param_id.ToString();
                lable_tmp.Size = new Size(60, 13);
                parameter_panel.Controls.Add(lable_tmp);




                //if typ -....

                //string ohne bereich = normale textbox
                if (split_construct[1] == "string" && split_construct.Length == 3)
                {
                    TextBox textbox_tmp = new TextBox();
                    textbox_tmp.Enabled = true;
                    textbox_tmp.Location = new Point(70, 20 + (40 * param_id));
                    textbox_tmp.Size = new Size(100, 20);
                    textbox_tmp.Name = "param_" + param_id.ToString();
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
                    tnud.Minimum = int.MinValue;
                    tnud.Maximum = int.MaxValue;
                    tnud.Value = 0;
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
             
                //inht mit num upo down
              //float mit num upd
                //bool checkbox



            }






 
          /*
            //VREATE TEXTBOX
            TextBox textbox_tmp = new TextBox();
            textbox_tmp.Enabled = true;
            textbox_tmp.Location = new Point(70,20+ (40* param_id));
            textbox_tmp.Size = new Size(100, 20);
            textbox_tmp.Name = "param_" + param_id.ToString();
            parameter_panel.Controls.Add(textbox_tmp);
            */




            load_parameters(ref parameter_panel);
        }

        public void load_parameters(ref Panel param_panel)
        {
            //wenn string != ""
            //durchsteppen und in die boxen schreiben

        }
    }
}
