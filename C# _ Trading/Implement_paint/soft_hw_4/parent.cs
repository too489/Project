using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using System.Data;
using System.Drawing.Imaging;

namespace soft_hw_4
{
    public partial class Parent : Form
    {
        Child child;
        private bool fill = false;
        public Parent()
        {
            InitializeComponent();
        }
        
        private void New_file_Click(object sender, EventArgs e)
        {
            child = new Child();
            child.MdiParent = this;
            child.Text = "제목없음";
            child.WindowState = FormWindowState.Maximized;
            child.Show();
            Save_file.Enabled = true;
            Image_Eraser.Enabled = true;
        }

        private void Open_file_Click(object sender, EventArgs e)
        {
            open_FD.Title = "이미지 읽기";
            open_FD.Filter = "(*.JPG)|*.JPG|(*.JPEG)|*.JPEG|(*.bmp)|*.bmp|(*.png)|*.png";
            open_FD.FilterIndex = 1;
            if (open_FD.ShowDialog() == DialogResult.OK)
            {
                child = new Child();
                child.MdiParent = this;
              //  MessageBox.Show(Path.GetFileName(open_FD.FileName));
                child.Text = Path.GetFileName(open_FD.FileName);
                

                child.setImage(open_FD.FileName);
                Width = child.Width+100;
                Height = child.Height+100;
                child.WindowState = FormWindowState.Maximized;
                child.Show();
                Save_file.Enabled = true;
                Image_Eraser.Enabled = true;

            }
        }//이미지를 원하는 형식으로만 받게 하였습니다

        private void Save_file_Click(object sender, EventArgs e)
        {
            child = (Child)(this.ActiveMdiChild);
            Save_FD.Title = "이미지 파일 저장 ";
            Save_FD.OverwritePrompt = true;
            Save_FD.Filter = "(*.JPG)|*.JPG|(*.JPEG)|*.JPEG|(*.bmp)|*.bmp|(*.png)|*.png";

            //이미지 파일 저장
            if (Save_FD.ShowDialog() == DialogResult.OK)
            {
                char spi = '.';

                string[] spstring = Save_FD.FileName.Split(spi);
                
                Bitmap bmp = new Bitmap(child.getPanel().Width- (16 * 3 + 12), child.getPanel().Height- (39 + 30));
                child.getPanel().DrawToBitmap(bmp, new Rectangle(0, 0, child.getPanel().Width - (16 * 3 + 12), child.getPanel().Height- (39 + 30)));
                
                if (File.Exists(Save_FD.FileName)) { File.Delete(Save_FD.FileName); }
                System.Drawing.Imaging.ImageFormat fmt = System.Drawing.Imaging.ImageFormat.Jpeg; bmp.Save(Save_FD.FileName, fmt);
                
                if (spstring[1].Equals("Png", StringComparison.OrdinalIgnoreCase))
                {
                    bmp.Save(Save_FD.FileName, ImageFormat.Png);
                }
                else if (spstring[1].Equals("Bmp", StringComparison.OrdinalIgnoreCase))
                {
                    bmp.Save(Save_FD.FileName, ImageFormat.Bmp);
                }
                else if ((spstring[1].Equals("JPG", StringComparison.OrdinalIgnoreCase)) || (spstring[1].Equals("jpeg", StringComparison.OrdinalIgnoreCase)))
                {
                    bmp.Save(Save_FD.FileName, ImageFormat.Jpeg);
                }
                child.Text = Path.GetFileName(Save_FD.FileName);
            }

        }//그림을 원하는 형식으로 저장하는 함수를 만들었습니다.

        private void Color_Change2_Click(object sender, EventArgs e)
        {
            if (color_D.ShowDialog() == DialogResult.OK)
            {
                Color_Change2.BackColor = color_D.Color;
                child.SetColor(Color_Change2.BackColor);
            }
        }
        
        private void toolStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            if (e.ClickedItem == line_select)
            {
                child.line = true;
                child.rect = false;
                child.circle = false;
                child.bru = false;
                child.pencil = false;
            }

            if (e.ClickedItem == square_select)
            {
                child.line = false;
                child.rect = true;
                child.circle = false;
                child.bru = false;
                child.pencil = false;
            }

            if (e.ClickedItem == round_select)
            {
                child.line = false;
                child.rect = false;
                child.circle = true;
                child.bru = false;
                child.pencil = false;
            }

            if(e.ClickedItem==pencil_select)
            {
                child.pencil = true;
                child.bru = false;
                child.line = false;
                child.rect = false;
                child.circle = false;
            }

            if (e.ClickedItem == paint_select)
            {
                child.bru = true;
                child.pencil = false;
                child.line = false;
                child.rect = false;
                child.circle = false;
            }

        }// 툴스트립을 항목별로 클릭할때 이벤트를 발생하게 하였습니다
        
        private void thick_1_Click(object sender, EventArgs e)
        {
            child.setThick(1);
        }
        private void thick_2_Click(object sender, EventArgs e)
        {
            child.setThick(2);
        }
        private void thick_3_Click(object sender, EventArgs e)
        {
            child.setThick(3);
        }
        private void thick_4_Click(object sender, EventArgs e)
        {
            child.setThick(4);
        }
        private void thick_5_Click(object sender, EventArgs e)
        {
            child.setThick(5);
        }
        private void 단색채우기ToolStripMenuItem_Click(object sender, EventArgs e)
        {
                fill = true;
                child.fillChange(fill);
        }
        private void 없음ToolStripMenuItem_Click(object sender, EventArgs e)
        {
                fill = false;
                child.fillChange(fill);
        }

        private void Image_Eraser_Click(object sender, EventArgs e)
        {
            child.clear_p();
            
        }
        
    }
}
