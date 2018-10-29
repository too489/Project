using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Collections;

namespace soft_hw_4
{
    public class MyCircle
    {
        private Rectangle rectC;
        private int thick;
        private bool fill;
        private Color color;
        public MyCircle()
        {
            rectC = new Rectangle();
        }

        public void setRectC(Point start,Point finish, int thick,bool fill,Color col)
        {
            rectC.X = Math.Min(start.X, finish.X);
            rectC.Y = Math.Min(start.Y, finish.Y);
            rectC.Width = Math.Abs(start.X - finish.X);
            rectC.Height = Math.Abs(start.Y - finish.Y);
            this.thick = thick;
            this.fill = fill;
            this.color = col;
        }

        public Rectangle getRectC()
        {
            return rectC;
        }
        public int getThick()
        {
            return thick;
        }
        public Color getColor()
        {
            return color;
        }
        public bool getfill()
        {
            return fill;
        }
    }
}
