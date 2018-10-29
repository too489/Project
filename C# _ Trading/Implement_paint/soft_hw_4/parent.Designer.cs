namespace soft_hw_4
{
    partial class Parent
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Parent));
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.이미지IToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.New_file = new System.Windows.Forms.ToolStripMenuItem();
            this.Open_file = new System.Windows.Forms.ToolStripMenuItem();
            this.Save_file = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.Exit_file = new System.Windows.Forms.ToolStripMenuItem();
            this.이미지IToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.Image_Eraser = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.Color_Change2 = new System.Windows.Forms.ToolStripButton();
            this.pencil_select = new System.Windows.Forms.ToolStripButton();
            this.paint_select = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.line_select = new System.Windows.Forms.ToolStripButton();
            this.square_select = new System.Windows.Forms.ToolStripButton();
            this.round_select = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton1 = new System.Windows.Forms.ToolStripDropDownButton();
            this.thick_1 = new System.Windows.Forms.ToolStripMenuItem();
            this.thick_2 = new System.Windows.Forms.ToolStripMenuItem();
            this.thick_3 = new System.Windows.Forms.ToolStripMenuItem();
            this.thick_4 = new System.Windows.Forms.ToolStripMenuItem();
            this.thick_5 = new System.Windows.Forms.ToolStripMenuItem();
            this.fillsquare_select = new System.Windows.Forms.ToolStripDropDownButton();
            this.채우기없음ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.단색채우기ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.없음ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.open_FD = new System.Windows.Forms.OpenFileDialog();
            this.Save_FD = new System.Windows.Forms.SaveFileDialog();
            this.color_D = new System.Windows.Forms.ColorDialog();
            this.Color_change = new System.Windows.Forms.ToolStripButton();
            this.thick1 = new System.Windows.Forms.ToolStripMenuItem();
            this.thick2 = new System.Windows.Forms.ToolStripMenuItem();
            this.thick3 = new System.Windows.Forms.ToolStripMenuItem();
            this.thick4 = new System.Windows.Forms.ToolStripMenuItem();
            this.thick5 = new System.Windows.Forms.ToolStripMenuItem();
            this.Tline_selec = new System.Windows.Forms.ToolStripDropDownButton();
            this.menuStrip1.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "new_image.png");
            this.imageList1.Images.SetKeyName(1, "circle_image.png");
            this.imageList1.Images.SetKeyName(2, "line_image.png");
            this.imageList1.Images.SetKeyName(3, "line0_image.png");
            this.imageList1.Images.SetKeyName(4, "line1_image.png");
            this.imageList1.Images.SetKeyName(5, "line2_image.png");
            this.imageList1.Images.SetKeyName(6, "line3_image.png");
            this.imageList1.Images.SetKeyName(7, "rect_image.png");
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.이미지IToolStripMenuItem,
            this.이미지IToolStripMenuItem1});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(775, 24);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 이미지IToolStripMenuItem
            // 
            this.이미지IToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.New_file,
            this.Open_file,
            this.Save_file,
            this.toolStripSeparator1,
            this.Exit_file});
            this.이미지IToolStripMenuItem.Name = "이미지IToolStripMenuItem";
            this.이미지IToolStripMenuItem.Size = new System.Drawing.Size(61, 20);
            this.이미지IToolStripMenuItem.Text = "파일((&F)";
            // 
            // New_file
            // 
            this.New_file.Name = "New_file";
            this.New_file.Size = new System.Drawing.Size(155, 22);
            this.New_file.Text = "새로 만들기(&N)";
            this.New_file.Click += new System.EventHandler(this.New_file_Click);
            // 
            // Open_file
            // 
            this.Open_file.Name = "Open_file";
            this.Open_file.Size = new System.Drawing.Size(155, 22);
            this.Open_file.Text = "열기(&O)";
            this.Open_file.Click += new System.EventHandler(this.Open_file_Click);
            // 
            // Save_file
            // 
            this.Save_file.Enabled = false;
            this.Save_file.Name = "Save_file";
            this.Save_file.Size = new System.Drawing.Size(155, 22);
            this.Save_file.Text = "저장(&S)";
            this.Save_file.Click += new System.EventHandler(this.Save_file_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(152, 6);
            // 
            // Exit_file
            // 
            this.Exit_file.Name = "Exit_file";
            this.Exit_file.Size = new System.Drawing.Size(155, 22);
            this.Exit_file.Text = "종료(&X)";
            // 
            // 이미지IToolStripMenuItem1
            // 
            this.이미지IToolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Image_Eraser});
            this.이미지IToolStripMenuItem1.Name = "이미지IToolStripMenuItem1";
            this.이미지IToolStripMenuItem1.Size = new System.Drawing.Size(66, 20);
            this.이미지IToolStripMenuItem1.Text = "이미지(&I)";
            // 
            // Image_Eraser
            // 
            this.Image_Eraser.Enabled = false;
            this.Image_Eraser.Name = "Image_Eraser";
            this.Image_Eraser.Size = new System.Drawing.Size(167, 22);
            this.Image_Eraser.Text = "이미지 지우기(N)";
            this.Image_Eraser.Click += new System.EventHandler(this.Image_Eraser_Click);
            // 
            // toolStrip1
            // 
            this.toolStrip1.Dock = System.Windows.Forms.DockStyle.Left;
            this.toolStrip1.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Color_Change2,
            this.pencil_select,
            this.paint_select,
            this.toolStripSeparator2,
            this.line_select,
            this.square_select,
            this.round_select,
            this.toolStripSeparator3,
            this.toolStripButton1,
            this.fillsquare_select});
            this.toolStrip1.Location = new System.Drawing.Point(0, 24);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.RenderMode = System.Windows.Forms.ToolStripRenderMode.System;
            this.toolStrip1.Size = new System.Drawing.Size(38, 502);
            this.toolStrip1.TabIndex = 2;
            this.toolStrip1.Text = "toolStrip1";
            this.toolStrip1.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.toolStrip1_ItemClicked);
            // 
            // Color_Change2
            // 
            this.Color_Change2.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.Color_Change2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.Color_Change2.Image = global::soft_hw_4.Properties.Resources.이름_없음1;
            this.Color_Change2.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.Color_Change2.Name = "Color_Change2";
            this.Color_Change2.Size = new System.Drawing.Size(35, 28);
            this.Color_Change2.Text = "toolStripButton1";
            this.Color_Change2.Click += new System.EventHandler(this.Color_Change2_Click);
            // 
            // pencil_select
            // 
            this.pencil_select.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.pencil_select.Image = ((System.Drawing.Image)(resources.GetObject("pencil_select.Image")));
            this.pencil_select.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.pencil_select.Name = "pencil_select";
            this.pencil_select.Size = new System.Drawing.Size(35, 28);
            this.pencil_select.Text = "toolStripButton2";
            // 
            // paint_select
            // 
            this.paint_select.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.paint_select.Image = ((System.Drawing.Image)(resources.GetObject("paint_select.Image")));
            this.paint_select.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.paint_select.Name = "paint_select";
            this.paint_select.Size = new System.Drawing.Size(35, 28);
            this.paint_select.Text = "toolStripButton3";
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(35, 6);
            // 
            // line_select
            // 
            this.line_select.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.line_select.Image = ((System.Drawing.Image)(resources.GetObject("line_select.Image")));
            this.line_select.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.line_select.Name = "line_select";
            this.line_select.Size = new System.Drawing.Size(35, 28);
            this.line_select.Text = "toolStripButton2";
            // 
            // square_select
            // 
            this.square_select.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.square_select.Image = ((System.Drawing.Image)(resources.GetObject("square_select.Image")));
            this.square_select.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.square_select.Name = "square_select";
            this.square_select.Size = new System.Drawing.Size(35, 28);
            this.square_select.Text = "toolStripButton2";
            // 
            // round_select
            // 
            this.round_select.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.round_select.Image = ((System.Drawing.Image)(resources.GetObject("round_select.Image")));
            this.round_select.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.round_select.Name = "round_select";
            this.round_select.Size = new System.Drawing.Size(35, 28);
            this.round_select.Text = "toolStripButton2";
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(35, 6);
            // 
            // toolStripButton1
            // 
            this.toolStripButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.thick_1,
            this.thick_2,
            this.thick_3,
            this.thick_4,
            this.thick_5});
            this.toolStripButton1.Image = global::soft_hw_4.Properties.Resources._3line;
            this.toolStripButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton1.Name = "toolStripButton1";
            this.toolStripButton1.Size = new System.Drawing.Size(35, 28);
            this.toolStripButton1.Text = "toolStripButton1";
            // 
            // thick_1
            // 
            this.thick_1.Name = "thick_1";
            this.thick_1.Size = new System.Drawing.Size(81, 22);
            this.thick_1.Text = "1";
            this.thick_1.Click += new System.EventHandler(this.thick_1_Click);
            // 
            // thick_2
            // 
            this.thick_2.Name = "thick_2";
            this.thick_2.Size = new System.Drawing.Size(81, 22);
            this.thick_2.Text = "2";
            this.thick_2.Click += new System.EventHandler(this.thick_2_Click);
            // 
            // thick_3
            // 
            this.thick_3.Name = "thick_3";
            this.thick_3.Size = new System.Drawing.Size(81, 22);
            this.thick_3.Text = "3";
            this.thick_3.Click += new System.EventHandler(this.thick_3_Click);
            // 
            // thick_4
            // 
            this.thick_4.Name = "thick_4";
            this.thick_4.Size = new System.Drawing.Size(81, 22);
            this.thick_4.Text = "4";
            this.thick_4.Click += new System.EventHandler(this.thick_4_Click);
            // 
            // thick_5
            // 
            this.thick_5.Name = "thick_5";
            this.thick_5.Size = new System.Drawing.Size(81, 22);
            this.thick_5.Text = "5";
            this.thick_5.Click += new System.EventHandler(this.thick_5_Click);
            // 
            // fillsquare_select
            // 
            this.fillsquare_select.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.채우기없음ToolStripMenuItem});
            this.fillsquare_select.Image = global::soft_hw_4.Properties.Resources.fillsquare;
            this.fillsquare_select.Name = "fillsquare_select";
            this.fillsquare_select.Size = new System.Drawing.Size(35, 28);
            // 
            // 채우기없음ToolStripMenuItem
            // 
            this.채우기없음ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.단색채우기ToolStripMenuItem,
            this.없음ToolStripMenuItem});
            this.채우기없음ToolStripMenuItem.Name = "채우기없음ToolStripMenuItem";
            this.채우기없음ToolStripMenuItem.Size = new System.Drawing.Size(138, 22);
            this.채우기없음ToolStripMenuItem.Text = "채우기 효과";
            // 
            // 단색채우기ToolStripMenuItem
            // 
            this.단색채우기ToolStripMenuItem.Name = "단색채우기ToolStripMenuItem";
            this.단색채우기ToolStripMenuItem.Size = new System.Drawing.Size(134, 22);
            this.단색채우기ToolStripMenuItem.Text = "단색채우기";
            this.단색채우기ToolStripMenuItem.Click += new System.EventHandler(this.단색채우기ToolStripMenuItem_Click);
            // 
            // 없음ToolStripMenuItem
            // 
            this.없음ToolStripMenuItem.Name = "없음ToolStripMenuItem";
            this.없음ToolStripMenuItem.Size = new System.Drawing.Size(134, 22);
            this.없음ToolStripMenuItem.Text = "없음";
            this.없음ToolStripMenuItem.Click += new System.EventHandler(this.없음ToolStripMenuItem_Click);
            // 
            // open_FD
            // 
            this.open_FD.FileName = "openFileDialog1";
            // 
            // Color_change
            // 
            this.Color_change.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.Color_change.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.Color_change.Checked = true;
            this.Color_change.CheckState = System.Windows.Forms.CheckState.Checked;
            this.Color_change.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.Color_change.ForeColor = System.Drawing.SystemColors.ControlDark;
            this.Color_change.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.Color_change.Name = "Color_change";
            this.Color_change.Size = new System.Drawing.Size(29, 20);
            // 
            // thick1
            // 
            this.thick1.Name = "thick1";
            this.thick1.Size = new System.Drawing.Size(81, 22);
            this.thick1.Text = "1";
            // 
            // thick2
            // 
            this.thick2.Name = "thick2";
            this.thick2.Size = new System.Drawing.Size(81, 22);
            this.thick2.Text = "2";
            // 
            // thick3
            // 
            this.thick3.Name = "thick3";
            this.thick3.Size = new System.Drawing.Size(81, 22);
            this.thick3.Text = "3";
            // 
            // thick4
            // 
            this.thick4.Name = "thick4";
            this.thick4.Size = new System.Drawing.Size(81, 22);
            this.thick4.Text = "4";
            // 
            // thick5
            // 
            this.thick5.Name = "thick5";
            this.thick5.Size = new System.Drawing.Size(81, 22);
            this.thick5.Text = "5";
            // 
            // Tline_selec
            // 
            this.Tline_selec.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.Tline_selec.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.thick1,
            this.thick2,
            this.thick3,
            this.thick4,
            this.thick5});
            this.Tline_selec.Image = ((System.Drawing.Image)(resources.GetObject("Tline_selec.Image")));
            this.Tline_selec.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.Tline_selec.Name = "Tline_selec";
            this.Tline_selec.Size = new System.Drawing.Size(29, 20);
            this.Tline_selec.Text = "3line_select";
            // 
            // Parent
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Black;
            this.ClientSize = new System.Drawing.Size(775, 526);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.menuStrip1);
            this.IsMdiContainer = true;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Parent";
            this.Text = "그림판";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.ImageList imageList1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 이미지IToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem New_file;
        private System.Windows.Forms.ToolStripMenuItem Open_file;
        private System.Windows.Forms.ToolStripMenuItem Save_file;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem Exit_file;
        private System.Windows.Forms.ToolStripMenuItem 이미지IToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem Image_Eraser;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton pencil_select;
        private System.Windows.Forms.ToolStripButton paint_select;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripButton line_select;
        private System.Windows.Forms.ToolStripButton square_select;
        private System.Windows.Forms.ToolStripButton round_select;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.OpenFileDialog open_FD;
        private System.Windows.Forms.SaveFileDialog Save_FD;
        private System.Windows.Forms.ColorDialog color_D;
        private System.Windows.Forms.ToolStripButton Color_change;
        private System.Windows.Forms.ToolStripButton Color_Change2;
        private System.Windows.Forms.ToolStripMenuItem thick1;
        private System.Windows.Forms.ToolStripMenuItem thick2;
        private System.Windows.Forms.ToolStripMenuItem thick3;
        private System.Windows.Forms.ToolStripMenuItem thick4;
        private System.Windows.Forms.ToolStripMenuItem thick5;
        private System.Windows.Forms.ToolStripDropDownButton Tline_selec;
        private System.Windows.Forms.ToolStripDropDownButton toolStripButton1;
        private System.Windows.Forms.ToolStripMenuItem thick_1;
        private System.Windows.Forms.ToolStripMenuItem thick_2;
        private System.Windows.Forms.ToolStripMenuItem thick_3;
        private System.Windows.Forms.ToolStripMenuItem thick_4;
        private System.Windows.Forms.ToolStripMenuItem thick_5;
        private System.Windows.Forms.ToolStripDropDownButton fillsquare_select;
        private System.Windows.Forms.ToolStripMenuItem 채우기없음ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 단색채우기ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 없음ToolStripMenuItem;
    }
}

