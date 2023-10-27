/*package sk.stuba.fei.uim.vsa.pr2.auth;

import lombok.extern.slf4j.Slf4j;
import sk.stuba.fei.uim.vsa.pr2.domain.Student;

import javax.annotation.Priority;
import javax.ws.rs.Priorities;
import javax.ws.rs.container.ContainerRequestContext;
import javax.ws.rs.container.ContainerRequestFilter;
import javax.ws.rs.container.ResourceInfo;
import javax.ws.rs.core.Context;
import javax.ws.rs.core.HttpHeaders;
import javax.ws.rs.core.Response;
import javax.ws.rs.ext.Provider;
import java.io.IOException;
import java.lang.reflect.Method;
import java.security.Principal;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

@Slf4j
@Secured
@Provider
@Priority(Priorities.AUTHORIZATION)
public class AuthorizationFilter implements ContainerRequestFilter {

    @Context
    private ResourceInfo resourceInfo;

    @Override
    public void filter(ContainerRequestContext request) throws IOException {
        Principal p =  request.getSecurityContext().getUserPrincipal();
        Method resourceMethod = resourceInfo.getResourceMethod();
        Set<Permision> permisions = extractPermisionsFromMethod(resourceMethod);

        log.info("resource class:"+ resourceInfo.getResourceClass());
        log.info("resource method:"+ resourceInfo.getResourceMethod());

        if (!permisions.isEmpty()) {
            if (student.getPermissions().stream().noneMatch(permisions::contains)) {
                request.abortWith(Response
                        .status(Response.Status.FORBIDDEN)
                        .build());

            }
        }





    }
    private Set<Permision> extractPermisionsFromMethod(Method method){
        if (method == null){
            return new HashSet<>();
        }
        Secured secured = method.getAnnotation(Secured.class);
        if (secured == null){
            return new HashSet<>();
        }
        return new HashSet<>(Arrays.asList(secured.value()));
    }
}
*/