package sk.stuba.fei.uim.vsa.pr2.web;

import org.glassfish.grizzly.http.server.HttpServer;
import org.glassfish.jersey.grizzly2.httpserver.GrizzlyHttpServerFactory;
import org.glassfish.jersey.server.ResourceConfig;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import sk.stuba.fei.uim.vsa.pr2.BCryptService;
import sk.stuba.fei.uim.vsa.pr2.JAXRSApplicationConfiguration;
import sk.stuba.fei.uim.vsa.pr2.auth.Permision;
import sk.stuba.fei.uim.vsa.pr2.domain.Student;
import sk.stuba.fei.uim.vsa.pr2.domain.Teacher;
import sk.stuba.fei.uim.vsa.pr2.domain.Thesis;
import sk.stuba.fei.uim.vsa.pr2.services.ThesisService;

import java.net.URI;
import java.security.acl.Permission;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static sk.stuba.fei.uim.vsa.pr2.ApplicationConfiguration.BASE_URI;

public class Project2Application {

    private final ThesisService service = new ThesisService();
    private static final Logger log = LoggerFactory.getLogger(Project2Application.class);

    public static HttpServer startServer() {
        final ResourceConfig rc = ResourceConfig.forApplicationClass(JAXRSApplicationConfiguration.class);
        log.info("Starting Grizzly2 HTTP server...");
        log.info("Server listening on " + BASE_URI);
        return GrizzlyHttpServerFactory.createHttpServer(URI.create(BASE_URI), rc);
    }

    public static void main(String[] args) {
        try {
            final HttpServer server = startServer();

            Runtime.getRuntime().addShutdownHook(new Thread(() -> {
                try {
                    ThesisService.getInstance().close();
                    log.info("Shutting down the application...");
                    server.shutdownNow();
                    log.info("Exiting");
                } catch (Exception e) {
                    log.error(e.getMessage(), e);
                }
            }));
            log.info("Last steps of setting up the application...");
            ThesisService service =  ThesisService.getInstance();
            List<Permision> list = new ArrayList<>();
            list.add(Permision.PERM_TO_GET);
            Student student = service.createStudent(1L,"Milan","marcel@what", BCryptService.hash("Mi"),1,1,"fei");
            Student student2 = service.createStudent(2L,"Marcel","marcel@whattt", BCryptService.hash("Ma"),2,2,"fei");
            Teacher teacher = service.createTeacher(1L,"Ivan","a@b.com",BCryptService.hash("Iv"),"FEI","FEI");
            Teacher teacher2 = service.createTeacher(2L,"Gregor","aaa@gg.com",BCryptService.hash("Ge"),"FEI","FEI");
            Thesis thesis1 = service.createThesis("DSDSDS","hod ostepom","BACHELOR","ako sa hadze ostep",teacher);
            Thesis thesis2 = service.createThesis("AAAAA","ako ovorti dvere","BACHELOR","otvorenie dveri",teacher2);





            postStart();
            log.info(String.format("Application started.%nStop the application using CRL+C"));
            Thread.currentThread().join();
        } catch (InterruptedException e) {
            log.error(e.getMessage(), e);
        }
    }


    public static void postStart() {
        // TODO sem napíš akékoľvek nastavenia, či volania, ktoré sa majú udiať ihneď po štarte servera

    }


}
