namespace SmartPLC_Commander
{
    partial class Form1
    {
        /// <summary>
        /// Erforderliche Designervariable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Verwendete Ressourcen bereinigen.
        /// </summary>
        /// <param name="disposing">True, wenn verwaltete Ressourcen gelöscht werden sollen; andernfalls False.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Vom Windows Form-Designer generierter Code

        /// <summary>
        /// Erforderliche Methode für die Designerunterstützung.
        /// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
        /// </summary>
        private void InitializeComponent()
        {
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.dateiToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.nodeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadAdditionalNodeConfigurationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.saveNodeSchematicToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripTextBox1 = new System.Windows.Forms.ToolStripTextBox();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.panel1 = new System.Windows.Forms.Panel();
            this.label2 = new System.Windows.Forms.Label();
            this.node_nsi_text = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.node_nid_text = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.node_title_text = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.parameter_panel_form = new System.Windows.Forms.Panel();
            this.label5 = new System.Windows.Forms.Label();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.menuStrip1.SuspendLayout();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            this.SuspendLayout();
            // 
            // treeView1
            // 
            this.treeView1.Location = new System.Drawing.Point(12, 27);
            this.treeView1.Name = "treeView1";
            this.treeView1.Size = new System.Drawing.Size(170, 388);
            this.treeView1.TabIndex = 1;
            this.treeView1.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.treeView1_AfterSelect);
            // 
            // dateiToolStripMenuItem
            // 
            this.dateiToolStripMenuItem.Name = "dateiToolStripMenuItem";
            this.dateiToolStripMenuItem.Size = new System.Drawing.Size(12, 23);
            // 
            // nodeToolStripMenuItem
            // 
            this.nodeToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.loadAdditionalNodeConfigurationToolStripMenuItem});
            this.nodeToolStripMenuItem.Name = "nodeToolStripMenuItem";
            this.nodeToolStripMenuItem.Size = new System.Drawing.Size(156, 23);
            this.nodeToolStripMenuItem.Text = "Load Node-Configuration";
            this.nodeToolStripMenuItem.Click += new System.EventHandler(this.nodeToolStripMenuItem_Click);
            // 
            // loadAdditionalNodeConfigurationToolStripMenuItem
            // 
            this.loadAdditionalNodeConfigurationToolStripMenuItem.Name = "loadAdditionalNodeConfigurationToolStripMenuItem";
            this.loadAdditionalNodeConfigurationToolStripMenuItem.Size = new System.Drawing.Size(267, 22);
            this.loadAdditionalNodeConfigurationToolStripMenuItem.Text = "Load additional Node-Configuration";
            this.loadAdditionalNodeConfigurationToolStripMenuItem.Click += new System.EventHandler(this.loadAdditionalNodeConfigurationToolStripMenuItem_Click);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.dateiToolStripMenuItem,
            this.nodeToolStripMenuItem,
            this.saveNodeSchematicToolStripMenuItem,
            this.toolStripTextBox1});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(821, 27);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // saveNodeSchematicToolStripMenuItem
            // 
            this.saveNodeSchematicToolStripMenuItem.Name = "saveNodeSchematicToolStripMenuItem";
            this.saveNodeSchematicToolStripMenuItem.Size = new System.Drawing.Size(135, 23);
            this.saveNodeSchematicToolStripMenuItem.Text = "Save Node-Schematic";
            this.saveNodeSchematicToolStripMenuItem.Click += new System.EventHandler(this.saveNodeSchematicToolStripMenuItem_Click);
            // 
            // toolStripTextBox1
            // 
            this.toolStripTextBox1.Name = "toolStripTextBox1";
            this.toolStripTextBox1.Size = new System.Drawing.Size(100, 23);
            this.toolStripTextBox1.Text = "192.168.178.58";
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.label5);
            this.panel1.Controls.Add(this.parameter_panel_form);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.node_nsi_text);
            this.panel1.Controls.Add(this.label4);
            this.panel1.Controls.Add(this.node_nid_text);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Controls.Add(this.node_title_text);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Location = new System.Drawing.Point(188, 30);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(182, 385);
            this.panel1.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(42, 5);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(73, 15);
            this.label2.TabIndex = 6;
            this.label2.Text = "Properties";
            // 
            // node_nsi_text
            // 
            this.node_nsi_text.AutoSize = true;
            this.node_nsi_text.Location = new System.Drawing.Point(53, 80);
            this.node_nsi_text.Name = "node_nsi_text";
            this.node_nsi_text.Size = new System.Drawing.Size(62, 13);
            this.node_nsi_text.TabIndex = 5;
            this.node_nsi_text.Text = "<node_nsi>";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(3, 80);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(31, 13);
            this.label4.TabIndex = 4;
            this.label4.Text = "NSI :";
            // 
            // node_nid_text
            // 
            this.node_nid_text.AutoSize = true;
            this.node_nid_text.Location = new System.Drawing.Point(53, 53);
            this.node_nid_text.Name = "node_nid_text";
            this.node_nid_text.Size = new System.Drawing.Size(63, 13);
            this.node_nid_text.TabIndex = 3;
            this.node_nid_text.Text = "<node_nid>";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(3, 53);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(32, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "NID :";
            // 
            // node_title_text
            // 
            this.node_title_text.AutoSize = true;
            this.node_title_text.Location = new System.Drawing.Point(53, 26);
            this.node_title_text.Name = "node_title_text";
            this.node_title_text.Size = new System.Drawing.Size(65, 13);
            this.node_title_text.TabIndex = 1;
            this.node_title_text.Text = "<node_title>";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 26);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "NODE :";
            // 
            // parameter_panel_form
            // 
            this.parameter_panel_form.Location = new System.Drawing.Point(6, 130);
            this.parameter_panel_form.Name = "parameter_panel_form";
            this.parameter_panel_form.Size = new System.Drawing.Size(173, 240);
            this.parameter_panel_form.TabIndex = 7;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(42, 112);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(81, 15);
            this.label5.TabIndex = 8;
            this.label5.Text = "Parameters";
            // 
            // numericUpDown1
            // 
            this.numericUpDown1.DecimalPlaces = 1;
            this.numericUpDown1.Increment = new decimal(new int[] {
            12,
            0,
            0,
            65536});
            this.numericUpDown1.Location = new System.Drawing.Point(499, 110);
            this.numericUpDown1.Minimum = new decimal(new int[] {
            -1591546464,
            7525,
            0,
            -2147483648});
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Size = new System.Drawing.Size(120, 20);
            this.numericUpDown1.TabIndex = 3;
            this.numericUpDown1.Value = new decimal(new int[] {
            15,
            0,
            0,
            65536});
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(821, 427);
            this.Controls.Add(this.numericUpDown1);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.treeView1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Form1";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.TreeView treeView1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem nodeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem dateiToolStripMenuItem;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.ToolStripMenuItem saveNodeSchematicToolStripMenuItem;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox1;
        private System.Windows.Forms.ToolStripMenuItem loadAdditionalNodeConfigurationToolStripMenuItem;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label node_nsi_text;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label node_nid_text;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label node_title_text;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Panel parameter_panel_form;
        private System.Windows.Forms.NumericUpDown numericUpDown1;
    }
}

