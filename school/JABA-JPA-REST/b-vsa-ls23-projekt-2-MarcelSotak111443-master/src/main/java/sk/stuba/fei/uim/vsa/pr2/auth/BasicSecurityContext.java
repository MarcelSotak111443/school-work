package sk.stuba.fei.uim.vsa.pr2.auth;


import sk.stuba.fei.uim.vsa.pr2.domain.Student;
import sk.stuba.fei.uim.vsa.pr2.domain.Teacher;

import javax.ws.rs.core.SecurityContext;
import java.security.Principal;

public class BasicSecurityContext implements SecurityContext {

    private Principal user;
    private boolean isSecure;

    public void setSecure(boolean secure) {
        isSecure = secure;

    }

    public BasicSecurityContext(Principal user) {
        this.user = user;
    }
    public BasicSecurityContext(Teacher user) {

    }

    @Override
    public Principal getUserPrincipal() {
        return user;
    }

    @Override
    public boolean isUserInRole(String s) {
        return true;
    }

    @Override
    public boolean isSecure() {
        return false;
    }

    @Override
    public String getAuthenticationScheme() {
        return "Basic";
    }
}
