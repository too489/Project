package user;

public class User {
	private String id;
    private String pw;
    private String name;
    private String email;
    private String de_Name;
    private int prof;
    private String sec1;
    private String sec2;
    private String sec3;
    private String sec4;
    
    public String getSec4() {
		return sec4;
	}
	public void setSec4(String sec4) {
		this.sec4 = sec4;
	}
	public String getSec1() {
		return sec1;
	}
	public void setSec1(String sec1) {
		this.sec1 = sec1;
	}
	public String getSec2() {
		return sec2;
	}
	public void setSec2(String sec2) {
		this.sec2 = sec2;
	}
	public String getSec3() {
		return sec3;
	}
	public void setSec3(String sec3) {
		this.sec3 = sec3;
	}
	
	public String getId() {
		return id;
	}
	public void setId(String id) {
		this.id = id;
	}
	public String getPw() {
		return pw;
	}
	public void setPw(String pw) {
		this.pw = pw;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getEmail() {
		return email;
	}
	public void setEmail(String email) {
		this.email = email;
	}
	public String getDe_Name() {
		return de_Name;
	}
	public void setDe_Name(String de_Name) {
		this.de_Name = de_Name;
	}
	public int getProf() {
		return prof;
	}
	public void setProf(int prof) {
		this.prof = prof;
	}


    
}