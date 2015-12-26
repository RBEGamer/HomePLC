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
