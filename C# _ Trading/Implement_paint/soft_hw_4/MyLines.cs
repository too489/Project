using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Collections;

namespace soft_hw_4
{
    public class MyLines
    {
        private Point[] point = new Point[2];
        private float thick;
        private bool fill;
        private Color color;
        public MyLines()
        {
            point[0] = new Point();
            point[1] = new Point();
        }

        public void setPoint(Point start, Point finish, float thick, bool fill, Color col)
        {
            point[0]= start;
            point[1] = finish;
            this.thick = thick;
            this.fill=fill;
            this.color = col;
        }
        public Point getPoint1()
        {
            return point[0];
        }
        public Point getPoint2()
        {
            return point[1];
        }
        public float getThick()
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

