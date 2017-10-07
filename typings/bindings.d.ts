declare module "bindings" {

	function bindings<T>(name: string): T;

	namespace bindings {
		// Empty
	}

	export = bindings;
}
