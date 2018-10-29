<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
    <link rel="stylesheet" href="css/CheckBox.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
    <title>Join</title>
  </head>
  <body>
<nav class="navbar navbar-default">
      <div class="navbar-header">
         <button type="button"class= "navbar-toggle collapsed"
         data-toggle="collapse" data-target="#bs-example-navbar-collapse-1"
         aria-expanded="false">
         <span class="icon-bar"></span>
         <span class="icon-bar"></span>
         <span class="icon-bar"></span>
         </button>
         <a class="navbar-brand" href="main_s.jsp"> KwMain</a>
      </div>
      <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
         <ul class="nav navbar-nav">
            <li><a href="mini_ucam.jsp">Mini_Ucam</a></li>
            <li><a href="kw_bbs.jsp">KW_LIFE</a></li>
         </ul>
         <ul class="nav navbar-nav navbar-right">
            <li class ="dropdown">
               <a href="#" class="dropdown-toggle"
                  data-toggle="dropdown" role = "button" aria-haspopup="true"
                  aria-expanded="false"> 접속하기<span class ="caret"></span></a>
               <ul class="dropdown-menu">
                     <li><a href="login_s.jsp">로그인</a></li>
                     <li class="active"> <a href="join_s.jsp">회원가입</a></li>
                     
              </ul>
            </li>
         </ul>
      </div>
   </nav>
   <div class= "container">
      <div class = "col-lg-9" ></div>
      <div class = "col-lg-59">
         <div class = "jumbotron" style="padding-top : 20px;">
          <form method="post" action ="joinAction_s.jsp">
            <h3 style ="text-align:center;">회원가입 화면</h3>
            <div class="form-group">
               <input type="text" class="form-control" placeholder ="아이디 " name="id" maxlength="20">
            </div>
            <div class="form-group">
               <input type="password" class="form-control" placeholder ="비밀번호" name="pw" maxlength="20">
            </div>
            <div class="form-group">
               <input type="text" class="form-control" placeholder ="이름 " name="name" maxlength="20">
            </div>
            <div class="form-group">
               <input type="email" class="form-control" placeholder ="E-Mail" name="email" maxlength="20">
            </div>
            
             <div class="form-group" style="text-align:center;">
                <div class="btn-group" data-toggle="buttons">
                    <label class="btn btn-default">
					<input type="radio" autocomplete="off" value="소프트웨어학과" name="de_Name">소프트웨어학과
					</label>
			
	                <label class="btn btn-default">
					<input type="radio" autocomplete="off" value="컴퓨터공학과" name="de_Name">컴퓨터공학과
					</label>
				</div>
			</div>
		<div class="container">
  			<div class="column">
            <div class="form-group"  style="text-align:center;">
                <label class="btn btn-default" >
					 <input type="checkbox" autocomplete="off" name="sec1" value="데이터베이스1">데이터 베이스
				</label>
		
                <label class="btn btn-default">
					 <input type="checkbox" autocomplete="off" name="sec2" value="데이터베이스2">데이터 베이스1
				</label>
			
                <label class="btn btn-default">
					 <input type="checkbox" autocomplete="off" name="sec3" value="데이터베이스3">알고리즘 1
				</label>
			
                <label class="btn btn-default">
					 <input type="checkbox" autocomplete="off" name= "sec4" value="데이터베이스1">알고리즘 2
				</label>
			</div>
			</div>
			</div>
            <input type="submit" class="btn btn-primary form-control" value="회원가입">
         </form>
         </div>
      </div>
      <div class = "col-lg-4"></div>
      </div>
   <script src="https://code.jquery.com/jquery-3.1.1.min.js"></script>
   <script src="js/bootstrap.js"></script>
  </body>
</html>