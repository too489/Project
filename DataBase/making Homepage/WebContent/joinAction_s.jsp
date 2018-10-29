<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="user.UserDAO" %>
<%@ page import="java.io.PrintWriter" %>
<%   request.setCharacterEncoding("UTF-8");%>
<jsp:useBean id="user" class="user.User" scope="page"/>
<jsp:setProperty name="user" property="id"/>  
<jsp:setProperty name="user" property="pw"/>
<jsp:setProperty name="user" property="name"/>  
<jsp:setProperty name="user" property="email"/>  
<jsp:setProperty name="user" property="de_Name"/>
<jsp:setProperty name="user" property="sec1"/>
<jsp:setProperty name="user" property="sec2"/>
<jsp:setProperty name="user" property="sec3"/>
<jsp:setProperty name="user" property="sec4"/>


<!DOCTYPE html >
<html>
<body>
<%
   String userID=null;
   
   if(session.getAttribute("userID")!=null){
   userID=(String)session.getAttribute("userID");
   }
   
   if(userID!=null){
   PrintWriter script=response.getWriter();
   script.println("alert('이미 로그인이 되어있습니다.')");
   script.println("<script>");
   script.println("location.href='main_s.jsp'");
   script.println("</script>");   
   }
   System.out.println("뭐빠짐?"+user.getId()+" "+user.getPw()+" "+user.getName()+" "+user.getDe_Name()+" "+user.getEmail());
   if(user.getId()==null||user.getPw()==null||user.getName()==null||user.getDe_Name()==null||user.getEmail()==null)
   {
   PrintWriter script=response.getWriter();
   script.println("<script>");
   script.println("alert('입력이 안된 사항이 있습니다.')");
   script.println("history.back()");
   script.println("</script>");
   }
   if(user.getSec1()==null&&user.getSec2()==null&&user.getSec3()==null&&user.getSec4()==null)
    {     
    	  PrintWriter script=response.getWriter();
	      script.println("<script>");
	      script.println("alert('한 과목도 선택되지 않았습니다')");
	      script.println("history.back()");
	      script.println("</script>");
    }
   else
   {
      UserDAO userDAO=new UserDAO();
     int result=0;
      result=userDAO.join(user);
      System.out.println(result);
      if(result ==-1){
         PrintWriter script=response.getWriter();
         script.println("<script>");
         script.println("alert('이미 존재하는 아이디입니다.')");
         script.println("history.back()");
         script.println("</script>");
      }
      else{
        session.setAttribute("userID",user.getId());
         PrintWriter script=response.getWriter();
         script.println("<script>");
         script.println("alert('회원가입 완료!')");
         script.println("location.href='main_s.jsp'");
         script.println("</script>");
      } 
   }
 
%> 

</body>
</html>