using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Drawing.Imaging;
using System.ComponentModel;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using System.Data;
using System.Collections;
using soft_hw_4;

namespace soft_hw_4
{

    public partial class Child : Form
    {
        public ImageFormat ImageFormatPng { get; private set; }
        private Bitmap bit;
        Image picture;
        public bool line { set; get; }
        public bool rect { set; get; }
        public bool circle { set; get; }
        public bool bru { set; get; }
        public bool pencil { set; get; }

        public bool fill = false;
        public int c_Width;
        public int c_Height;
        private Point start;
        private string path;
        private Point finish;
        private Pen pen;
        private SolidBrush brush;
        public int nline;
        public int nrect;
        public int ncircle;
        private int i;
        private int thick = 1;
        private Color color = Color.FromArgb(0, 0, 0);
        private MyLines[] mylines;
        private MyRect[] myrect;
        private MyCircle[] mycircle;
        public List<MyLines> mypen;
        Graphics g;
        public void fillChange(bool fi)
        {
            this.fill = fi;
        }
        public void SetupVar()
        {
            i = 0;
            thick = 1;
            line = false;
            rect = false;
            circle = false;
            bru = false;
            pencil = false;
            start = new Point(0, 0);
            finish = new Point(0, 0);
            pen = new Pen(Color.Black);
            mylines = new MyLines[100];
            mypen = new List<MyLines>();

            myrect = new MyRect[100];
            mycircle = new MyCircle[100];
            brush = new SolidBrush(Color.Black);

            nline = 0;
            nrect = 0;
            ncircle = 0;
            SetupMine();
        }

        private void SetupMine()
        {
            for (i = 0; i < 100; i++)
                mylines[i] = new MyLines();
            for (i = 0; i < 100; i++)
                myrect[i] = new MyRect();
            for (i = 0; i < 100; i++)
                mycircle[i] = new MyCircle();
        }
       
        public Child()
        {
            InitializeComponent();

            SetupVar();
//            child_panel.Refresh();
        }
        public void setThick(int size)
        {
            this.thick = size;
        }
        public Panel getPanel()
        {
            return this.doubleBufferPanel1;
        }//패널을 얻어오는값을 정하였습니다.
        public void setImage(string path1)
        {
            path = path1;
            picture = Image.FromFile(path);
            Width = picture.Width + 16 *3+12;
            Height = picture.Height + 39+30;
        }//크기를 설정해주었습니다 하지만 과제에서 제시한 값을적용시키면 조금 잘려서 값을 더주었습니다
        public void SetColor(Color co)
        {
            this.color = co;
        }

        private void child_panel_Paint(object sender, PaintEventArgs e)
        {
            g = e.Graphics;
            
            if (path != null)
            {
                g = e.Graphics;
            
            picture = Image.FromFile(path);
            
            g.DrawImage(picture, 0, 0);
            }
            e.Graphics.SmoothingMode = SmoothingMode.AntiAlias;//좀더 부드러운 효과를 위해 선언하였습니다

            for (i = 0; i <= nline; i++)
            {
                pen.Width = mylines[i].getThick();
                pen.DashStyle = DashStyle.Solid;
                pen.Color = mylines[i].getColor();
                brush.Color = mylines[i].getColor();
                e.Graphics.DrawLine(pen, mylines[i].getPoint1(), mylines[i].getPoint2());
            }

            for (i = 0; i <= nrect; i++)
            {
                pen.Width = myrect[i].getThick();
                pen.DashStyle = DashStyle.Solid;
                pen.Color = myrect[i].getColor();
                brush.Color = myrect[i].getColor();
                if (!myrect[i].getfill())
                {
                    e.Graphics.DrawRectangle(pen, myrect[i].getRect());

                }
                else
                {
                    e.Graphics.FillRectangle(brush, myrect[i].getRect());
                }
            }

            for (i = 0; i <= ncircle; i++)
            {
                pen.Width = mycircle[i].getThick();
                pen.DashStyle = DashStyle.Solid;
                pen.Color = mycircle[i].getColor();
                brush.Color = mycircle[i].getColor();
                if (!mycircle[i].getfill())
                {
                    e.Graphics.DrawEllipse(pen, mycircle[i].getRectC());
                }
                else
                {
                    e.Graphics.FillEllipse(brush, mycircle[i].getRectC());
                }
            }
            foreach (MyLines i in mypen)
            {
                pen.Width = i.getThick();
                pen.DashStyle = DashStyle.Solid;
                pen.Color = i.getColor();
                e.Graphics.DrawLine(pen, i.getPoint1(), i.getPoint2());
            }
            pen.Width = thick;
            pen.DashStyle = DashStyle.Solid;

            
            if (path != null)
            {
              //  g.Dispose();
              //  picture.Dispose();
            }
            // bit.Dispose();
        }
        

        private void child_panel_MouseUp(object sender, MouseEventArgs e)
        {
            if (line == true)
                nline++;
            if (rect == true)
                nrect++;
            if (circle == true)
                ncircle++;
            start.X = 0;
            start.Y = 0;
            finish.X = 0;
            finish.Y = 0;
        }//마우스가 띄어졌을때 초기화 시켜주는 함수입니다

        private void child_panel_MouseDown(object sender, MouseEventArgs e)
        {
            start.X = e.X;
            start.Y = e.Y;
        }

        private void child_panel_MouseMove(object sender, MouseEventArgs e)
        {
            if ((start.X == 0) && (start.Y == 0))
                return;

            finish.X = e.X;
            finish.Y = e.Y;
            Point curPoint = new Point(e.X,e.Y);

            if (line == true)
            {
                mylines[nline].setPoint(start, finish, thick, fill,color);
            }

            if (rect == true)
            {
                myrect[nrect].setRect(start, finish, thick, fill,color);

            }

            if (circle == true)
            {
                mycircle[ncircle].setRectC(start, finish, thick, fill,color);
            }

            if ((bru == true|| pencil == true )&& e.Button==MouseButtons.Left)
            {
                
                Pen pencile=new Pen(color);
                if (pencil)
                    pencile.Width = 1;
                else
                    pencile.Width = 5;
                MyLines my = new MyLines();
                my.setPoint(start,curPoint, pencile.Width, false, color);
                start = curPoint;
                mypen.Add(my);
            }

            doubleBufferPanel1.Invalidate(true);
            doubleBufferPanel1.Update();
        }

        public void clear_p()
        {

           
            nline = 0;
            nrect = 0;
            ncircle = 0;SetupMine();
            mypen.Clear();
            path = null;
            doubleBufferPanel1.Invalidate(true);
            doubleBufferPanel1.Update();
        }

        private void Child_Load(object sender, EventArgs e)
        {
            this.SetStyle(ControlStyles.OptimizedDoubleBuffer | ControlStyles.UserPaint | ControlStyles.AllPaintingInWmPaint, true);
            this.UpdateStyles();
        }
    }
}
