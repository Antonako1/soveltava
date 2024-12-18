/**
 * 
 * @param name "FIRST;NAME" typed name
 */
export const parse_name = (name: string | undefined, space:boolean=false): string => {
    if (!name) {
        return "";
    }
    const res = name.split(";").map((n) => n.charAt(0).toUpperCase() + n.slice(1).toLowerCase()).join(" ");
    return space ? " " + res : res;
}

export const parse_first_name = (name: string | undefined, space:boolean=false): string => {
    if (!name) {
        return "";
    }
    const res = name.split(";")[0].charAt(0).toUpperCase() + name.split(";")[0].slice(1).toLowerCase();
    return space ? " " + res : res;
}

export const parse_last_name = (name: string | undefined, space:boolean=false): string => {
    if (!name) {
        return "";
    }
    const res = name.split(";")[1].charAt(0).toUpperCase() + name.split(";")[1].slice(1).toLowerCase();
    return space ? " " + res : res;
}

