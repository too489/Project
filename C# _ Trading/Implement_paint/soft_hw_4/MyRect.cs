using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Collections;

namespace soft_hw_4
{
    public class MyRect
    {
        private Rectangle rect;
        private int thick;
        private bool fill;
        private Color color;

        public MyRect()
        {
            rect = new Rectangle();
        }

        public void setRect(Point start,Point finish, int thick,bool fill,Color col)
        {
            rect.X = Math.Min(start.X, finish.X);
            rect.Y = Math.Min(start.Y, finish.Y);
            rect.Width = Math.Abs(start.X - finish.X);
            rect.Height = Math.Abs(start.Y - finish.Y);
            this.thick = thick;
            this.fill = fill;
            this.color = col;
        }

        public Rectangle getRect()
        {
            return rect;
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
