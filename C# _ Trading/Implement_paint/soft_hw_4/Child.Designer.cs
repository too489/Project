namespace soft_hw_4
{
    partial class Child
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.doubleBufferPanel1 = new soft_hw_4.DoubleBufferPanel();
            this.SuspendLayout();
            // 
            // doubleBufferPanel1
            // 
            this.doubleBufferPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.doubleBufferPanel1.Location = new System.Drawing.Point(0, 0);
            this.doubleBufferPanel1.Name = "doubleBufferPanel1";
            this.doubleBufferPanel1.Size = new System.Drawing.Size(1018, 875);
            this.doubleBufferPanel1.TabIndex = 0;
            this.doubleBufferPanel1.Paint += new System.Windows.Forms.PaintEventHandler(this.child_panel_Paint);
            this.doubleBufferPanel1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.child_panel_MouseDown);
            this.doubleBufferPanel1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.child_panel_MouseMove);
            this.doubleBufferPanel1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.child_panel_MouseUp);
            // 
            // Child
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1018, 875);
            this.Controls.Add(this.doubleBufferPanel1);
            this.Name = "Child";
            this.Text = "제목 없음";
            this.Load += new System.EventHandler(this.Child_Load);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.child_panel_Paint);
            this.ResumeLayout(false);

        }

        #endregion
        private DoubleBufferPanel doubleBufferPanel1;
    }
}